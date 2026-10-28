#include "driver/adc.h"
#include "esp_adc_cal.h"

#define CANAL_ADC ADC1_CHANNEL_6   // GPIO 34

vacio tarea_lectura(vacio *arg) {
    mientras (verdadero) {
        entero valor = adc1_get_raw(CANAL_ADC);
        LOG_INFO("Valor ADC: %d", valor);
        retardo_ms(500);
    }
}

principal() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(CANAL_ADC, ADC_ATTEN_DB_11);

    LOG_INFO("ADC inicializado en GPIO 34 (canal 6)");
    tarea(tarea_lectura, "tarea_adc");

    mientras (verdadero) {
        retardo_ms(1000);
    }
}
