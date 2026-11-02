incluir "driver/rtc_io.h"
incluir "esp_sleep.h"

#definir PIN_BOTON 33

// Variable que sobrevive al deep sleep
ATRIBUTO_DATOS_RTC entero contador_despertares = 0;

vacio imprimir_causa(entero causa) {
    segun (causa) {
        caso CAUSA_DESPERTAR_EXT0:
            LOG_INFO("Despertar por boton (EXT0)");
            romper;
        caso CAUSA_DESPERTAR_TEMPORIZADOR:
            LOG_INFO("Despertar por temporizador");
            romper;
        por_defecto:
            LOG_INFO("Despertar por otra causa: %d", causa);
            romper;
    }
}

principal() {
    contador_despertares = contador_despertares + 1;
    LOG_INFO("Arranque numero: %d", contador_despertares);

    // Mostrar por que hemos despertado
    entero causa = obtener_causa_despertar();
    imprimir_causa(causa);

    // Configurar el pin del boton como RTC GPIO con pull-down
    si (es_gpio_rtc_valido(PIN_BOTON)) {
        deshabilitar_pullup_rtc(PIN_BOTON);
        habilitar_pulldown_rtc(PIN_BOTON);
        LOG_INFO("Boton configurado en GPIO %d como RTC GPIO", PIN_BOTON);
    } sino {
        LOG_ERROR("GPIO %d no es valido para RTC", PIN_BOTON);
    }

    // Despertar cuando el boton pase a nivel alto
    habilitar_despertar_ext0(PIN_BOTON, 1);

    LOG_INFO("Entrando en deep sleep. Pulsa el boton para despertar...");
    retardo_ms(100);   // dar tiempo al log a salir por UART antes de dormir

    iniciar_sueno_profundo();

    // Nunca se llega aqui
}
