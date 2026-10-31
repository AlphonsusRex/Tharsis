incluir "driver/dac.h"

#definir CANAL_DAC CANAL_DAC_1   // GPIO 25

vacio tarea_onda(vacio *arg) {
    entero valor = 0;
    entero paso = 1;
    
    mientras (verdadero) {
        escribir_voltaje_dac(CANAL_DAC, valor);
        
        valor = valor + paso;
        si (valor >= 255) {
            paso = -1;
        }
        si (valor <= 0) {
            paso = 1;
        }
        
        retardo_ms(10);  // 10ms para evitar el watchdog
    }
}

principal() {
    habilitar_dac(CANAL_DAC);
    LOG_INFO("DAC inicializado en GPIO 25 (canal 1)");
    
    cCrearTarea(tarea_onda, "tarea_dac", 2048, nulo, 1, nulo);
    
    mientras (verdadero) {
        LOG_INFO("Generando onda triangular...");
        retardo_ms(1000);
    }
}
