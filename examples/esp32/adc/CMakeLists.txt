cmake_minimum_required(VERSION 3.16)

# Registrar la carpeta include/ de la raíz de Tharsis como componente
set(EXTRA_COMPONENT_DIRS "../../../include")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(tharsis_adc)
