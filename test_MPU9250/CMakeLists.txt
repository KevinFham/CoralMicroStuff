add_executable_m7(test_MPU9250
    test_MPU9250.cc
)

target_link_libraries(test_MPU9250
    libs_base-m7_freertos
)