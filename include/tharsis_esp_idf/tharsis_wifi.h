#ifndef THARSIS_WIFI_H
#define THARSIS_WIFI_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

// Variable para saber si estamos conectados
static EventGroupHandle_t tharsis_wifi_event_group;
#define THARSIS_CONECTADO_BIT BIT0
static int tharsis_wifi_reintentos = 0;

// Manejador de eventos interno de Tharsis
static void tharsis_wifi_event_handler(void* arg, esp_event_base_t event_base,
                                       int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (tharsis_wifi_reintentos < 5) {
            esp_wifi_connect();
            tharsis_wifi_reintentos++;
            ESP_LOGW("WiFi", "Reintentando conexion (%d/5)...", tharsis_wifi_reintentos);
        } else {
            xEventGroupClearBits(tharsis_wifi_event_group, THARSIS_CONECTADO_BIT);
            ESP_LOGE("WiFi", "Fallo al conectar. Revisa SSID/Password.");
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI("WiFi", "Conectado! IP: " IPSTR, IP2STR(&event->ip_info.ip));
        tharsis_wifi_reintentos = 0;
        xEventGroupSetBits(tharsis_wifi_event_group, THARSIS_CONECTADO_BIT);
    }
}

// Función principal que el usuario llamará
static inline void iniciar_wifi(const char* ssid, const char* password) {
    ESP_LOGI("WiFi", "Iniciando conexion a %s...", ssid);

    // 1. Inicializar NVS (necesario para WiFi)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // 2. Inicializar TCP/IP y Event Loop
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    // 3. Inicializar WiFi en modo Estación
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // 4. Registrar eventos
    tharsis_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &tharsis_wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &tharsis_wifi_event_handler, NULL));

    // 5. Configurar SSID y Password
    wifi_config_t wifi_config = {0};
    strncpy((char*)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char*)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    // 6. Esperar a que se conecte (con timeout de 10 segundos)
    EventBits_t bits = xEventGroupWaitBits(tharsis_wifi_event_group,
            THARSIS_CONECTADO_BIT,
            pdFALSE,
            pdFALSE,
            pdMS_TO_TICKS(10000));

    if (bits & THARSIS_CONECTADO_BIT) {
        ESP_LOGI("WiFi", "WiFi listo y funcionando.");
    } else {
        ESP_LOGE("WiFi", "Timeout esperando conexion.");
    }
}

#endif // THARSIS_WIFI_H
