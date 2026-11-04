idf_component_register(SRCS "wifi.c"
                       INCLUDE_DIRS "." "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include"
                       PRIV_REQUIRES driver esp_driver_gpio esp_wifi nvs_flash esp_event esp_netif)
