# Contexto del Proyecto: Tharsis (v0.6.0)

## 1. ¿Qué es Tharsis?
Transpilador de C a "C con palabras clave en español" para ESP32.
- **Filosofía:** No es un lenguaje nuevo. Es C estándar donde se sustituyen tokens.
- **Arquitectura:** 
  - `tharsis_gen.cpp`: El transpilador.
  - `include/tharsis_esp_idf/*.h`: Headers con `#define` y macros que traducen ESP-IDF.
  - `test/golden/`: 13 golden tests.
  - `examples/esp32/`: Ejemplos funcionales.

## 2. Estado Actual (v0.6.0)
- **Periféricos implementados y probados en hardware real (ESP32-WROOM-32 / DevKit V1):**
  - GPIO (Blinky)
  - ADC (Potenciómetro)
  - DAC (Onda triangular)
  - RTC GPIO + Deep Sleep (EXT0 en pin 33)
  - MCPWM (PWM Avanzado con nueva API de IDF v5.5)
  - **WiFi (Conexión STA en 1 línea):** Probado con éxito conectando a red Movistar y obteniendo IP.
- **Git:** Rama `v0.3`, tag `v0.6.0`.

## 3. Próximos Pasos (Roadmap Robot)
Para construir el robot, faltan:
1. **I2C:** Para leer sensores (MPU6050, ultrasonidos).
2. **Interrupciones GPIO:** Para leer encoders de ruedas o el HC-SR04.
3. **HTTP Client o MQTT:** Para enviar datos al móvil o a la nube.

## 4. Archivos Clave para adjuntar
1. `tharsis_gen.cpp`
2. `README.md`
3. `include/tharsis_esp_idf.h`
4. `include/tharsis_esp_idf/tharsis_wifi.h`
