# Tharsis

Transpilador de C con sintaxis en español, enfocado a microcontroladores ESP32 con ESP-IDF.

## Qué es

Tharsis te permite escribir C con palabras clave en español (`entero`, `si`, `mientras`, `imprimir`...) y compilarlo con el mismo toolchain de C que ya usas. El `.c` generado es legible y editable.

**No es un lenguaje nuevo**: es C con keywords en español. Todo lo que sabes de C y ESP-IDF sigue aplicando.

## Estado

- **v0.2.0**: transpilador host funcional, 12 golden tests en verde.
- **Próximo**: modo `--modo idf` para compilar con `idf.py` y correr en ESP32 real.

## Instalación

```bash
git clone https://github.com/TU-USUARIO/tharsis.git
cd tharsis
g++ -std=c++17 -O2 tharsis_gen.cpp -o tharsis_gen

