###############################################################
###################### Project Settings #######################
###############################################################
cmake_minimum_required(VERSION 3.6)
project("Pistache")
# C++ 17 Standard
add_definitions("-std=c++17")
# Resolve Linker Error
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

###############################################################
################## Dependencies & Libraries ###################
###############################################################
# conan (pistache, rapidjson)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

###############################################################
######################### Executables #########################
###############################################################
# Server
add_executable("${PROJECT_NAME}Server" src/server.cpp)
target_link_libraries("${PROJECT_NAME}Server" ${CONAN_LIBS})
# Client
add_executable("${PROJECT_NAME}Client" src/client.cpp)
target_link_libraries("${PROJECT_NAME}Client" ${CONAN_LIBS})
