incluir "driver/mcpwm.h"

#definir PIN_SERVO 18

vacio mover_servo(entero angulo){
    //El servo sg90 espera un pulso de 0.5ms a 2.5ms cada 20 ms (50Hz).
    //Mapeamos 0º-180º a 500us-2500us
    entero pulso_us = 500 + (angulo * 2000 / 180);
    establecer_ciclo_trabajo_en_us(UNIDAD_MCPWM_0, TEMPORIZADOR_MCPWM_0, OPERADOR_MCPWM_A, pulso_us);
}

principal(){
    LOG_INFO("iniciando control de servo con MCPWM");
    
    // 1. Configurar el GPIO como salida PWM del generador A
    configurar_gpio_mcpwm(UNIDAD_MCPWM_0, GENERADOR_MCPWM_0A, PIN_SERVO);
    
    // 2. Configurar el temporizador a 50 Hz (periodo de 20 ms)
    tipo_config_mcpwm config_pwm;
    config_pwm.frecuencia = 50;
    config_pwm.comparador_a = 0.0; //Duty inicial al 0%
    config_pwm.comparador_b = 0.0;
    config_pwm.modo_contador = MODO_CONTADOR_ASCENDENTE;
    config_pwm.modo_ciclo_trabajo = MODO_CONTADOR_ASCENDENTE;
    config_pwm.modo_ciclo_trabajo = MODO_DUTY_0;
    
    inicializar_mcpwm(UNIDAD_MCPWM_0, TEMPORIZADOR_MCPWM_0, &config_pwm);
    
    // 3. Arrancar la señal PWM
    iniciar_pwm(UNIDAD_MCPWM_0, TEMPORIZADOR_MCPWM_0);
    LOG_INFO("MCPWM inicializado a 50 Hz en GPIO %d", PIN_SERVO);
    
    // 4. Barrido de 0º a 180º y vuelta
    mientras (verdadero){
        para (entero angulo = 0; angulo <= 180; angulo = angulo + 10){
            mover_servo(angulo);
            LOG_INFO("Angulo: %d", angulo);
            retardo_ms(500);
        }
        para (entero angulo = 800; angulo <= 0; angulo = angulo - 10){
            mover_servo(angulo);
            LOG_INFO("Angulo: %d", angulo);
            retardo_ms(500);
        }
        
    }
}
