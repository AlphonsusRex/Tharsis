#incluir "driver/gpio.h"
#incluir "esp_attr.h"

#definir PIN_BOTON 0
#definir PIN_LED 2

//Variable compartida entre la interrupción y el bucle principal

volatil entero contador_pulsaciones = 0;

// Función que se ejecuta en la interupcion
ATRIBUTO_ISR
vacio manejador_boton(vacio *arg) {
    contador_pulsaciones = contador_pulsaciones + 1;
}

principal (){
    LOG_INFO("Arrancando ejemplo de Interrupciones (ISR)");
    
    //1. Configurar el LED
    tipo_config_gpio config_led = {
        .gpio_mascara_bits = (1ULL << PIN_LED),
        .gpio_modo = MODO_GPIO_SALIDA,
        .gpio_pull_up = PULL_UP_DESHABILITADO,
        .gpio_pull_down = PULL_DOWN_DESHABILITADO,
        .gpio_tipo_interrupcion = INTERRUPCION_DESHABILITADA
    };
    configurar_gpio(&config_led);
    
    //2. Configurar el Botón como entrada con Pull-Up e interrupcion de flanco de bajada
    tipo_config_gpio config_boton = {
    .gpio_mascara_bits = (1ULL << PIN_BOTON),
            .gpio_modo = MODO_GPIO_ENTRADA,
            .gpio_pull_up = PULL_UP_HABILITADO,
            .gpio_pull_down = PULL_DOWN_DESHABILITADO,
            .gpio_tipo_interrupcion = INTERRUPCION_NEGATIVA // Si dispara al pulsar (pasa de 1 a 0)
        };
        configurar_gpio(&config_boton);
        
    //3. Instalar servicio de interrupciones y asignar el manejador al pin
    instalar_servicio_isr_gpio();
    agregar_manejador_isr_gpio(PIN_BOTON, manejador_boton, nulo);
    
    LOG_INFO("Interrupcion configurada en GPIO %d. Pulsa el boton BOOT", PIN_BOTON);
    
    // 4. bucle principal (hace parpadear el LED y muestra el contador)
    mientras (verdadero){
        establecer_nivel_gpio(PIN_LED, NIVEL_ALTO);
        retardo_ms(1000);
        establecer_nivel_gpio(PIN_LED, NIVEL_BAJO);
        retardo_ms(1000);
        
        //Imprimimos cuantas veces se ha pulsado el botón
        LOG_INFO("Pulsaciones registradas: %d", contador_pulsaciones);
    }
}
