incluir "driver/adc.h"

#definir CANAL_ADC CANAL_ADC_1_6   // GPIO 34

vacio tarea_lectura(vacio *arg) {
    mientras (verdadero) {
        entero valor = leer_adc_1_crudo(CANAL_ADC);
        LOG_INFO("Valor ADC: %d", valor);
        retardo_ms(500);
    }
}

principal() {
    configurar_ancho_adc_1(ANCHO_ADC_12_BITS);
    configurar_atenuacion_canal_adc_1(CANAL_ADC, ATENUACION_ADC_11_DB);

    LOG_INFO("ADC inicializado en GPIO 34 (canal 6)");
    cCrearTarea(tarea_lectura, "tarea_adc", 2048, nulo, 1, nulo);

    mientras (verdadero) {
        retardo_ms(1000);
    }
}
