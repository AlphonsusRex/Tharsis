#include "driver/gpio.h"

#define LED_GPIO 2

principal() {
    gpio_config_t config_led = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&config_led);

    mientras (verdadero) {
        gpio_set_level(LED_GPIO, 1);
        retardo(500);
        gpio_set_level(LED_GPIO, 0);
        retardo(500);
    }

    retornar 0;
}
