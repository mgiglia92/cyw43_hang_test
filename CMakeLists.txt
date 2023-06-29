cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11) 
set(CMAKE_CXX_STANDARD 17)


include(pico_sdk_import.cmake)
pico_sdk_init()
project(cyw43_hang_test C CXX ASM)


macro(make_exec exec_name exec_dir)
    add_executable(${exec_name} ${exec_dir})
    
    pico_add_extra_outputs(${exec_name})

    pico_enable_stdio_usb(${exec_name} 1)
    pico_enable_stdio_uart(${exec_name} 0)

    target_compile_definitions(${exec_name} PUBLIC
                            WIFI_SSID=\"${WIFI_SSID}\"
                            WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
                            # PICO_CYW43_ARCH_BACKGROUND
                            PICO_CYW43_ARCH_none
                            CYW43_HOST_NAME=\"${CYW43_HOST_NAME}\"
    )

    target_include_directories(${exec_name} PUBLIC
                            ${CMAKE_CURRENT_LIST_DIR}
                            ${PICO_SDK_PATH} 
                            
    )

    target_link_libraries(${exec_name}
                            # pico_cyw43_arch_lwip_threadsafe_background
                            pico_cyw43_arch_none
                            pico_stdlib
                            hardware_adc
                            hardware_pwm
                            hardware_irq
                            hardware_i2c
    )



endmacro()
make_exec(cyw43_hang cyw43_hang.cpp)
make_exec(cyw43_no_hang cyw43_no_hang.cpp)
