#ifndef THARSIS_DAC_H
#define THARSIS_DAC_H

#include "driver/dac.h"

// --- Funciones ---
#define habilitar_dac(canal)                dac_output_enable(canal)
#define deshabilitar_dac(canal)             dac_output_disable(canal)
#define escribir_voltaje_dac(canal, valor)  dac_output_voltage(canal, valor)

// --- Canales ---

#define CANAL_DAC_1 DAC_CHANNEL_1   //GPIO25

#define CANAL_DAC_2 DAC_CHANNEL_2   //GPIO26

#endif // THARSIS_DAC_H
