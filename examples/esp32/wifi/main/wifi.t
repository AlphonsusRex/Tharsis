#definir PIN_LED 2 
#definir MI_SSD "MOVISTAR_0BE0"
#definir MI_PASS "3qeN7FdWjff4KCqFi4i7"

principal(){
    LOG_INFO("Arrancando el ejemplo WiFi de Tharsis");
    
     // 1. Configurar el LED como salida (¡Esto faltaba!)
    tipo_config_gpio config_led = {
        .gpio_mascara_bits = (1ULL << PIN_LED),
        .gpio_modo = MODO_GPIO_SALIDA,
        .gpio_pull_up = PULL_UP_DESHABILITADO,
        .gpio_pull_down = PULL_DOWN_DESHABILITADO,
        .gpio_tipo_interrupcion = INTERRUPCION_DESHABILITADA
    };
    configurar_gpio(&config_led);
    
    //La famosa linea de una sola instrucción
    iniciar_wifi(MI_SSD, MI_PASS);
    
    //Bucle para demostrar que el chip sigue funcionando tras conectar
    
    mientras(verdadero){
        establecer_nivel_gpio(PIN_LED, NIVEL_ALTO);
        retardo_ms(500);
        establecer_nivel_gpio(PIN_LED, NIVEL_BAJO);
        retardo_ms(500);
    }
}
