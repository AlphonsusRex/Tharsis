#ifndef THARSIS_ESP_IDF_H
#define THARSIS_ESP_IDF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// TAG por defecto (el usuario puede sobreescribirlo en su .t)
#ifndef TAG
#define TAG "tharsis"
#endif

// --- Mapeo de la función principal ---
#define principal app_main

// --- Entrada / salida ---
#define imprimir(...) ESP_LOGI(TAG, __VA_ARGS__)
#define LOG_INFO(...)  ESP_LOGI(TAG, __VA_ARGS__)
#define LOG_AVISO(...) ESP_LOGW(TAG, __VA_ARGS__)
#define LOG_ERROR(...) ESP_LOGE(TAG, __VA_ARGS__)

// --- FreeRTOS ---
#define retardo_ms(ms) vTaskDelay(pdMS_TO_TICKS(ms))
#define retardo(ms)    vTaskDelay(pdMS_TO_TICKS(ms))
#define cCrearTarea(func, nombre, pila, arg, prio, handle) \
    xTaskCreate(func, nombre, pila, arg, prio, handle)

#endif // THARSIS_ESP_IDF_H
