idf_component_register(SRCS "dac.c"
                       INCLUDE_DIRS "." "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include"
                       PRIV_REQUIRES driver esp_adc)
