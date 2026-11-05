incluir "driver/i2c_master.h"

#definir PIN_SDA 21
#definir PIN_SCL 22

principal() {
    LOG_INFO("Arrancando Escaner I2C de Tharsis");

    tipo_manejador_bus_i2c bus = nulo;
    tipo_config_bus_i2c_maestro config_bus = {
        .puerto_i2c = PUERTO_I2C_0,
        .pin_sda = PIN_SDA,
        .pin_scl = PIN_SCL,
        .fuente_reloj_i2c = RELOJ_I2C_POR_DEFECTO,
        .flags = { .enable_internal_pullup = verdadero },
        .conteo_ignorar_glitch = 7
    };

    crear_bus_i2c(&config_bus, &bus);
    LOG_INFO("Bus I2C inicializado en SDA:%d, SCL:%d", PIN_SDA, PIN_SCL);

    entero dispositivos_encontrados = 0;
    LOG_INFO("Escaneando bus...");

    para (entero dir = 8; dir < 120; dir++) {
        si (probar_dispositivo_i2c(bus, dir, 50) == ESP_OK) {
            LOG_INFO("-> Dispositivo encontrado en 0x%02X", dir);
            dispositivos_encontrados = dispositivos_encontrados + 1;
        }
    }

    si (dispositivos_encontrados == 0) {
        LOG_AVISO("No se encontraron dispositivos I2C. Revisa el cableado.");
    } sino {
        LOG_INFO("Escaneo terminado. Encontrados: %d", dispositivos_encontrados);
    }

    mientras (verdadero) {
        retardo_ms(5000);
    }
}
