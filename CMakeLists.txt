project(LOVCI CXX)
cmake_minimum_required(VERSION 3.10)

find_package(Eigen3 REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(lovci
    # src/Core_functions.cpp
    # src/Input_Reader.cpp
    # src/Ladder.cpp
    src/LOVCI.cpp
)
target_link_libraries(lovci Eigen3::Eigen OpenMP::OpenMP_CXX)
