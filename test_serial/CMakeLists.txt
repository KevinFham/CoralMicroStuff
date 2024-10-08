add_executable_m7(test_serial
    test_serial.cc
)

target_link_libraries(test_serial
    libs_base-m7_freertos
)