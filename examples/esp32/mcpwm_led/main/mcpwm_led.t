incluir "driver/mcpwm_prelude.h"

#definir PIN_LED 18

principal() {
    LOG_INFO("Iniciando PWM para LED con MCPWM (nueva API)");

    // 1. Crear el temporizador
    tipo_temporizador_mcpwm timer = nulo;
    tipo_config_temporizador_mcpwm config_timer = {
        .grupo_id = 0,
        .fuente_reloj = RELOJ_POR_DEFECTO,
        .resolucion_hz = 1000000,   // 1 MHz -> 1 tick = 1 µs
        .periodo_ticks = 1000,      // 1000 ticks = 1 ms -> 1 kHz
        .modo_conteo = MODO_CONTEO_ASCENDENTE
    };
    crear_temporizador_mcpwm(&config_timer, &timer);

    // 2. Crear el operador
    tipo_operador_mcpwm oper = nulo;
    tipo_config_operador_mcpwm config_oper = {
        .grupo_id = 0
    };
    crear_operador_mcpwm(&config_oper, &oper);

    // 3. Conectar timer al operador
    conectar_temporizador_operador(oper, timer);

    // 4. Crear el comparador
    tipo_comparador_mcpwm comparador = nulo;
    tipo_config_comparador_mcpwm config_comparador = {
        .flags.update_cmp_on_tez = verdadero
    };
    crear_comparador_mcpwm(oper, &config_comparador, &comparador);

    // 5. Crear el generador
    tipo_generador_mcpwm generador = nulo;
    tipo_config_generador_mcpwm config_generador = {
        .gpio_generador = PIN_LED
    };
    crear_generador_mcpwm(oper, &config_generador, &generador);

    // 6. Configurar las acciones del generador
    // Al inicio del periodo (timer vacío) -> nivel ALTO
    configurar_accion_generador(generador, DIRECCION_ASCENDENTE, EVENTO_VACIO, ACCION_ALTO);
    // Al alcanzar el comparador -> nivel BAJO (duty cycle)
    configurar_accion_comparador(generador, DIRECCION_ASCENDENTE, comparador, ACCION_BAJO);

    // 7. Habilitar e iniciar el timer
    habilitar_temporizador_mcpwm(timer);
    iniciar_temporizador_mcpwm(timer, INICIO_CONTINUO_MCPWM);

    LOG_INFO("PWM inicializado a 1kHz en GPIO %d", PIN_LED);

    // 8. Bucle de fade
    mientras (verdadero) {
        // Subir brillo (duty de 0 a 1000 ticks)
        para (entero i = 0; i <= 1000; i = i + 25) {
            establecer_comparacion_mcpwm(comparador, i);
            retardo_ms(50);
        }
        // Bajar brillo
        para (entero i = 1000; i >= 0; i = i - 25) {
            establecer_comparacion_mcpwm(comparador, i);
            retardo_ms(50);
        }
    }
}
