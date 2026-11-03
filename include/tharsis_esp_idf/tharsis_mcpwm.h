#ifndef THARSIS_MCPWM_H
#define THARSIS_MCPWM_H

#include "driver/mcpwm_prelude.h"

// ============================================================
// MCPWM — Nueva API (ESP-IDF v5.x)
// ============================================================

// --- Tipos de handle (objetos opacos) ---
#define tipo_temporizador_mcpwm  mcpwm_timer_handle_t
#define tipo_operador_mcpwm      mcpwm_oper_handle_t
#define tipo_comparador_mcpwm    mcpwm_cmpr_handle_t
#define tipo_generador_mcpwm     mcpwm_gen_handle_t

// --- Estructuras de configuración ---
#define tipo_config_temporizador_mcpwm  mcpwm_timer_config_t
#define tipo_config_operador_mcpwm      mcpwm_operator_config_t
#define tipo_config_comparador_mcpwm    mcpwm_comparator_config_t
#define tipo_config_generador_mcpwm     mcpwm_generator_config_t

// --- Mapeo de campos (Timer) ---
#define grupo_id                group_id
#define fuente_reloj            clk_src
#define resolucion_hz           resolution_hz
#define periodo_ticks           period_ticks
#define modo_conteo             count_mode

// --- Mapeo de campos (Operador) ---
// (group_id ya está definido arriba)

// --- Mapeo de campos (Comparador) ---
// (no tiene campos adicionales relevantes para este ejemplo)

// --- Mapeo de campos (Generador) ---
#define gpio_generador          gen_gpio_num

// --- Constantes (Modos de conteo) ---
#define MODO_CONTEO_ASCENDENTE   MCPWM_TIMER_COUNT_MODE_UP
#define MODO_CONTEO_DESCENDENTE  MCPWM_TIMER_COUNT_MODE_DOWN
#define MODO_CONTEO_ASC_DESC     MCPWM_TIMER_COUNT_MODE_UP_DOWN

// --- Constantes (Fuente de reloj) ---
#define RELOJ_POR_DEFECTO        MCPWM_TIMER_CLK_SRC_DEFAULT

// --- Constantes (Acciones del generador) ---
#define ACCION_ALTO              MCPWM_GEN_ACTION_HIGH
#define ACCION_BAJO              MCPWM_GEN_ACTION_LOW
#define ACCION_MANTENER          MCPWM_GEN_ACTION_KEEP
#define ACCION_INVERTIR          MCPWM_GEN_ACTION_TOGGLE

// --- Constantes (Eventos del timer) ---
#define EVENTO_VACIO             MCPWM_TIMER_EVENT_EMPTY
#define EVENTO_PICO              MCPWM_TIMER_EVENT_FULL

// --- Constantes (Dirección del timer) ---
#define DIRECCION_ASCENDENTE     MCPWM_TIMER_DIRECTION_UP
#define DIRECCION_DESCENDENTE    MCPWM_TIMER_DIRECTION_DOWN

// --- Constantes (iniciar timer) ---
#define INICIO_CONTINUO_MCPWM MCPWM_TIMER_START_NO_STOP

// ============================================================
// Macros de conveniencia para crear objetos
// ============================================================

// Crear temporizador
#define crear_temporizador_mcpwm(config, handle) \
    mcpwm_new_timer((config), (handle))

// Crear operador
#define crear_operador_mcpwm(config, handle) \
    mcpwm_new_operator((config), (handle))

// Conectar temporizador al operador
#define conectar_temporizador_operador(oper, timer) \
    mcpwm_operator_connect_timer((oper), (timer))

// Crear comparador
#define crear_comparador_mcpwm(oper, config, handle) \
    mcpwm_new_comparator((oper), (config), (handle))

// Crear generador
#define crear_generador_mcpwm(oper, config, handle) \
    mcpwm_new_generator((oper), (config), (handle))

// Configurar acción del generador en evento de timer
#define configurar_accion_generador(generador, direccion, evento, accion) \
    mcpwm_generator_set_action_on_timer_event( \
        (generador), \
        MCPWM_GEN_TIMER_EVENT_ACTION((direccion), (evento), (accion)) \
    )

// Configurar acción del generador en evento de comparación
#define configurar_accion_comparador(generador, direccion, comparador, accion) \
    mcpwm_generator_set_action_on_compare_event( \
        (generador), \
        MCPWM_GEN_COMPARE_EVENT_ACTION((direccion), (comparador), (accion)) \
    )

// Habilitar y iniciar el timer
#define habilitar_temporizador_mcpwm(timer) \
    mcpwm_timer_enable((timer))

#define iniciar_temporizador_mcpwm(timer, comando) \
    mcpwm_timer_start_stop((timer), (comando))

// Establecer valor de comparación (duty)
#define establecer_comparacion_mcpwm(comparador, valor) \
    mcpwm_comparator_set_compare_value((comparador), (valor))

#endif // THARSIS_MCPWM_H
