idf_component_register(SRCS "blinky.c"
                       INCLUDE_DIRS "." "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include"
                       PRIV_REQUIRES driver)
