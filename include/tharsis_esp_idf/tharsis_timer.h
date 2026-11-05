#ifndef THARSIS_TIMER_H
#define THARSIS_TIMER_H

#include "esp_timer.h"

// =======================================================
// Temporizador de Alta Resolución (esp_timer)
// =======================================================

// --- Tipo de dato usado para guardar los tiempos
#define tipo_tiempo_us int64_t

// --- Obtener el tiempo actual sn microsegundos desde el arranque ---
#define obtener_tiempo_us() esp_timer_get_time()

#endif // THARSIS_TIMER_H
