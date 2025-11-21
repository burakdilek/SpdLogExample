cmake_minimum_required(VERSION 3.10)
project(SpdLogExample)

set(CMAKE_CXX_STANDARD 17)

# Yerel lib klasörünü include ve link yollarına ekle
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib)

# RPATH ayarları - uygulama çalıştırılırken lib klasöründeki .so dosyalarını bulsun
set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_BUILD_RPATH "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library(logger SHARED
    spdlog_xml_lib.cpp
)

target_include_directories(logger
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(logger
    PRIVATE
        pthread
        tinyxml2
)

add_executable(test_app
    test_app.cpp
)

target_link_libraries(test_app
    PRIVATE
        logger
)

