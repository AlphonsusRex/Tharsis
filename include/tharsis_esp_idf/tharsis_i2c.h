#ifndef THARSIS_I2C_H
#define THARSIS_I2C_H

#include "driver/i2c_master.h"

#define tipo_manejador_bus_i2c          i2c_master_bus_handle_t
#define tipo_manejador_dispositivo_i2c  i2c_master_dev_handle_t
#define tipo_config_bus_i2c_maestro     i2c_master_bus_config_t
#define tipo_config_dispositivo_i2c     i2c_device_config_t

// Mapeo de campos (sin colisiones)
#define puerto_i2c              i2c_port
#define pin_sda                 sda_io_num
#define pin_scl                 scl_io_num
#define fuente_reloj_i2c        clk_source
#define conteo_ignorar_glitch   glitch_ignore_cnt
#define direccion_i2c           device_address
#define velocidad_reloj_hz      scl_speed_hz

#define PUERTO_I2C_0            I2C_NUM_0
#define PUERTO_I2C_1            I2C_NUM_1
#define RELOJ_I2C_POR_DEFECTO   I2C_CLK_SRC_DEFAULT

#define crear_bus_i2c(config, manejador) \
    i2c_new_master_bus((config), (manejador))

#define agregar_dispositivo_i2c(bus, config, manejador) \
    i2c_master_bus_add_device((bus), (config), (manejador))

#define probar_dispositivo_i2c(bus, direccion, timeout_ms) \
    i2c_master_probe((bus), (direccion), (timeout_ms))

#define transmitir_i2c(dispositivo, datos, longitud, timeout_ms) \
    i2c_master_transmit((dispositivo), (datos), (longitud), (timeout_ms))

#define recibir_i2c(dispositivo, buffer, longitud, timeout_ms) \
    i2c_master_receive((dispositivo), (buffer), (longitud), (timeout_ms))

#endif // THARSIS_I2C_H
