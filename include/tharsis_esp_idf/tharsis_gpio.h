#ifndef THARSIS_GPIO_H
#define THARSIS_GPIO_H

#include "driver/gpio.h"

// --- Funciones ---
#define configurar_gpio(cfg)                gpio_config(cfg)
#define establecer_nivel_gpio(pin, nivel)   gpio_set_level(pin, nivel)
#define leer_nivel_gpio(pin)                gpio_get_level(pin)
#define configurar_direccion_gpio(pin, dir) gpio_set_direction(pin, dir)
#define configurar_pullup_gpio(pin, en)     gpio_set_pull_mode(pin, en)

// --- Tipos ---
#define tipo_config_gpio    gpio_config_t
#define modo_gpio           gpio_mode_t
#define nivel_gpio          gpio_num_t

// --- Campos de la estructura ---
#define gpio_mascara_bits       pin_bit_mask
#define gpio_modo               mode
#define gpio_pull_up            pull_up_en
#define gpio_pull_down          pull_down_en
#define gpio_tipo_interrupcion  intr_type

// --- Constantes (Modos) ---
#define MODO_GPIO_SALIDA         GPIO_MODE_OUTPUT
#define MODO_GPIO_ENTRADA        GPIO_MODE_INPUT
#define MODO_GPIO_ENTRADA_SALIDA GPIO_MODE_INPUT_OUTPUT
#define MODO_GPIO_ANALOGICO      GPIO_MODE_ANALOG
#define MODO_GPIO_DESHBILITADO    GPIO_MODE_DISABLE

// --- Constantes (Pull Up/Down) ---
#define PULL_UP_DESHABILITADO   GPIO_PULLUP_DISABLE
#define PULL_UP_HABILITADO      GPIO_PULLUP_ENABLE
#define PULL_DOWN_DESHABILITADO GPIO_PULLDOWN_DISABLE
#define PULL_DOWN_HABILITADO    GPIO_PULLDOWN_ENABLE
#define PULL_UP_DOWN_FLOTANTE   GPIO_PULLUP_PULLDOWN

// --- Constantes (Interrupciones) ---
#define INTERRUPCION_DESHABILITADA GPIO_INTR_DISABLE
#define INTERRUPCION_POSITIVA      GPIO_INTR_POSEDGE
#define INTERRUPCION_NEGATIVA      GPIO_INTR_NEGEDGE
#define INTERRUPCION_CUALQUIER     GPIO_INTR_ANYEDGE
#define INTERRUPCION_FLANCO_BAJO   GPIO_INTR_LOW_LEVEL
#define INTERRUPCION_FLANCO_ALTO   GPIO_INTR_HIGH_LEVEL

// --- Niveles ---
#define NIVEL_BAJO 0
#define NIVEL_ALTO 1

#endif // THARSIS_GPIO_H
