incluir "driver/gpio.h"
incluir "esp_attr.h"
incluir "esp_timer.h"

#definir PIN_BOTON 4   // <-- Cambia a 4 (o 15, el que uses para el cable)
#definir PIN_LED 2

volatil tipo_tiempo_us ultimo_tiempo = 0;
volatil tipo_tiempo_us diferencia_tiempo = 0;

ATRIBUTO_ISR
vacio manejador_boton(vacio *arg) {
    tipo_tiempo_us ahora = obtener_tiempo_us();
    si (ultimo_tiempo != 0) {
        diferencia_tiempo = ahora - ultimo_tiempo;
    }
    ultimo_tiempo = ahora;
}

principal() {
    LOG_INFO("Arrancando ejemplo de Temporizador");

    tipo_config_gpio config_led = {
        .gpio_mascara_bits = (1ULL << PIN_LED),
        .gpio_modo = MODO_GPIO_SALIDA,
        .gpio_pull_up = PULL_UP_DESHABILITADO,
        .gpio_pull_down = PULL_DOWN_DESHABILITADO,
        .gpio_tipo_interrupcion = INTERRUPCION_DESHABILITADA
    };
    configurar_gpio(&config_led);

    tipo_config_gpio config_boton = {
        .gpio_mascara_bits = (1ULL << PIN_BOTON),
        .gpio_modo = MODO_GPIO_ENTRADA,
        .gpio_pull_up = PULL_UP_HABILITADO, // Mantiene el pin en 3.3V cuando no tocas GND
        .gpio_pull_down = PULL_DOWN_DESHABILITADO,
        .gpio_tipo_interrupcion = INTERRUPCION_NEGATIVA // Se dispara al conectar a GND
    };
    configurar_gpio(&config_boton);

    instalar_servicio_isr_gpio();
    agregar_manejador_isr_gpio(PIN_BOTON, manejador_boton, nulo);
    
    LOG_INFO("Toca con un cable el GPIO %d y GND para medir el tiempo...", PIN_BOTON);

    mientras (verdadero) {
        si (diferencia_tiempo > 0) {
            LOG_INFO("Tiempo entre pulsos: %lld microsegundos", diferencia_tiempo);
            diferencia_tiempo = 0;
        }
        establecer_nivel_gpio(PIN_LED, NIVEL_ALTO);
        retardo_ms(500);
        establecer_nivel_gpio(PIN_LED, NIVEL_BAJO);
        retardo_ms(500);
    }
}
