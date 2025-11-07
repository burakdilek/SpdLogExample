cmake_minimum_required(VERSION 3.10)
project(SpdLogExample)

set(CMAKE_CXX_STANDARD 17)

# Yerel lib klasörünü include ve link yollarına ekle
include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# RPATH ayarları - uygulama çalıştırılırken lib klasöründeki .so dosyalarını bulsun
set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_BUILD_RPATH "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(spdlog_xml_example main.cpp)

target_link_libraries(spdlog_xml_example
    PRIVATE
        pthread
        tinyxml2
)
