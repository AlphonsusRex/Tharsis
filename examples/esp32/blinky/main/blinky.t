#include "driver/gpio.h"

#definir PIN_LED 2

principal() {
    tipo_config_gpio config_led = {
        .gpio_mascara_bits = (1ULL << PIN_LED),
        .gpio_modo = MODO_GPIO_SALIDA,
        .gpio_pull_up = PULL_UP_DESHABILITADO,
        .gpio_pull_down = PULL_DOWN_DESHABILITADO,
        .gpio_tipo_interrupcion = INTERRUPCION_DESHABILITADA
    };
    configurar_gpio(&config_led);

    mientras (verdadero) {
        establecer_nivel_gpio(PIN_LED, NIVEL_ALTO);
        retardo(500);
        establecer_nivel_gpio(PIN_LED, NIVEL_BAJO);
        retardo(500);
    }

    retornar;
}
