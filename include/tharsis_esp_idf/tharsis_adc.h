#ifndef THARSIS_ADC_H
#define THARSIS_ADC_H

#include "driver/adc.h"

#define configurar_ancho_adc_1(ancho) adc1_config_width(ancho)
#define configurar_atenuacion_canal_adc_1(canal, atenuacion) adc1_config_channel_atten(canal, atenuacion)
#define leer_adc_1_crudo(canal) adc1_get_raw(canal)

// --- Canales (ADC1) ---
#define CANAL_ADC_1_0 ADC1_CHANNEL_0
#define CANAL_ADC_1_1 ADC1_CHANNEL_1
#define CANAL_ADC_1_2 ADC1_CHANNEL_2
#define CANAL_ADC_1_3 ADC1_CHANNEL_3
#define CANAL_ADC_1_4 ADC1_CHANNEL_4
#define CANAL_ADC_1_5 ADC1_CHANNEL_5
#define CANAL_ADC_1_6 ADC1_CHANNEL_6
#define CANAL_ADC_1_7 ADC1_CHANNEL_7

// --- Ancho de bits ---
#define ANCHO_ADC_9_BITS ADC_WIDTH_BIT_9
#define ANCHO_ADC_10_BITS ADC_WIDTH_BIT_10
#define ANCHO_ADC_11_BITS ADC_WIDTH_BIT_11
#define ANCHO_ADC_12_BITS ADC_WIDTH_BIT_12

// --- Atenuacion ---
#define ATENUACION_ADC_0_DB ADC_ATTEN_DB_0
#define ATENUACION_ADC_2_5_DB ADC_ATTEN_DB_2_5
#define ATENUACION_ADC_6_DB ADC_ATTEN_DB_6
#define ATENUACION_ADC_11_DB ADC_ATTEN_DB_12

#endif // THARSIS_ADC_H
