#ifndef THARSIS_ISR_H
#define THARSIS_ISR_H

#include "driver/gpio.h"
#include "esp_attr.h"

// ======================================================
// Interrupciones
// ======================================================

// --- Atributo para funciones ISR (IRAM) ---
#define ATRIBUTO_ISR            IRAM_ATTR

// --- gESTIÓN DEL SERVICIO DE INTERRUPCIONES ---
#define instalar_servicio_isr_gpio()\
    gpio_install_isr_service(0)
    
#define agregar_manejador_isr_gpio(pin, manejador, arg)\
    gpio_isr_handler_add((pin), (manejador), (arg))
    
#define eliminar_manejador_isr_gpio()\
    gpio_isr_handler_remove((pin))
    
#endif // THARSIS_ISR_H
