cmake_minimum_required(VERSION 3.24)
project(DMaTGColloquium)

set(CMAKE_CXX_STANDARD 17)

add_executable(DMaTGColloquium 
    main.cpp 
    NaturalNumber.cpp 
    NaturalNumber.h 
    IntegerNumber.cpp 
    IntegerNumber.h 
    Exceptions/UniversalStringException.h 
    RationalNumber.cpp 
    RationalNumber.h 
    Polynomial.cpp 
    Polynomial.h
)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
# enable_testing()
# add_executable(IntegerTest
#     tests/IntegerTest.cpp
#     IntegerNumber.cpp
#     NaturalNumber.cpp
# )
# target_link_libraries(IntegerTest 
#     gtest_main 
# )