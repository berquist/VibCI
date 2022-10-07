find_package(Python3 REQUIRED)

macro(add_lovci_test TEST_NAME)
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/runtest.py ${CMAKE_BINARY_DIR}/lovci ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}
    )
endmacro(add_lovci_test name)

add_lovci_test(1D_cubic)
# add_lovci_test(2D_Drude)
# add_lovci_test(3D_cubic)
add_lovci_test(C2v_pot)
add_lovci_test(Harmonic)
