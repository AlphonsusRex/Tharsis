#ifndef THARSIS_RTC_GPIO_H
#define THARSIS_RTC_GPIO_H

#include "driver/rtc_io.h"
#include "esp_sleep.h"

// ============================================================
// RTC GPIO — Configuración de pines que sobreviven al deep sleep
// ============================================================

// --- Utilidades de validación ---
#define es_gpio_rtc_valido(pin)     rtc_gpio_is_valid_gpio(pin)

// --- Pull-up / Pull-down en dominio RTC ---
// Nota: en deep sleep los pull-up/down normales no funcionan;
// hay que usar estos, que dependen del dominio RTC_PERIPH.
#define habilitar_pullup_rtc(pin)   rtc_gpio_pullup_en(pin)
#define deshabilitar_pullup_rtc(pin) rtc_gpio_pullup_dis(pin)
#define habilitar_pulldown_rtc(pin) rtc_gpio_pulldown_en(pin)
#define deshabilitar_pulldown_rtc(pin) rtc_gpio_pulldown_dis(pin)

// --- Hold (mantener el nivel del pin durante el sleep) ---
#define retener_gpio_rtc(pin)       rtc_gpio_hold_en(pin)
#define liberar_gpio_rtc(pin)       rtc_gpio_hold_dis(pin)

// --- Desinicialización (volver a GPIO digital normal) ---
#define desinicializar_gpio_rtc(pin) rtc_gpio_deinit(pin)

// ============================================================
// Deep Sleep — Fuentes de despertar y control
// ============================================================

// --- Despertar por pin externo (EXT0) ---
// Solo pines RTC válidos. Nivel 0 = bajo, 1 = alto.
#define habilitar_despertar_ext0(pin, nivel) \
    esp_sleep_enable_ext0_wakeup((gpio_num_t)(pin), (nivel))

// --- Despertar por temporizador (microsegundos) ---
#define habilitar_despertar_temporizador(us) \
    esp_sleep_enable_timer_wakeup((uint64_t)(us))

// --- Entrar en deep sleep ---
#define iniciar_sueno_profundo()    esp_deep_sleep_start()

// --- Causa del último despertar ---
#define obtener_causa_despertar()   esp_sleep_get_wakeup_cause()

// ============================================================
// Constantes de causa de despertar
// ============================================================
#define CAUSA_DESPERTAR_EXT0        ESP_SLEEP_WAKEUP_EXT0
#define CAUSA_DESPERTAR_EXT1        ESP_SLEEP_WAKEUP_EXT1
#define CAUSA_DESPERTAR_TEMPORIZADOR ESP_SLEEP_WAKEUP_TIMER
#define CAUSA_DESPERTAR_TOUCHPAD    ESP_SLEEP_WAKEUP_TOUCHPAD
#define CAUSA_DESPERTAR_ULP         ESP_SLEEP_WAKEUP_ULP
#define CAUSA_DESPERTAR_UNDEFINIDA  ESP_SLEEP_WAKEUP_UNDEFINED

// ============================================================
// Atributo para variables que persisten en RTC memory
// ============================================================
#define ATRIBUTO_DATOS_RTC         RTC_DATA_ATTR

#endif // THARSIS_RTC_GPIO_H
