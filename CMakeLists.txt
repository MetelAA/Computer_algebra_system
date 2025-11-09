cmake_minimum_required(VERSION 3.24)
project(DMaTGColloquium)

set(CMAKE_CXX_STANDARD 17)

# ========== Основная программа ==========
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
    Validator/Validator.cpp 
    Validator/Validator.h 
    Validator/Utils/Lexer.cpp 
    Validator/Utils/Lexer.h 
    Validator/Utils/Monom.h 
    Validator/Utils/Parser.cpp 
    Validator/Utils/Parser.h 
    Validator/Utils/Token.cpp 
    Validator/Utils/Token.h
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(IntegerNumberTests
    tests/IntegerNumberTests.cpp
    IntegerNumber.cpp
    NaturalNumber.cpp
)
target_link_libraries(IntegerNumberTests 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(IntegerNumberTests)
add_executable(RationalNumberTests
    tests/RationalNumberTests.cpp
    RationalNumber.cpp
    IntegerNumber.cpp
    NaturalNumber.cpp
)
target_link_libraries(RationalNumberTests 
    gtest_main
)

gtest_discover_tests(RationalNumberTests)