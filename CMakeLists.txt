cmake_minimum_required(VERSION 3.10)
project(SpdLogExample)

set(CMAKE_CXX_STANDARD 17)

# Kütüphanelerin .so dosyalarını bulmak için
find_package(spdlog REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(spdlog_xml_example main.cpp)

target_link_libraries(spdlog_xml_example
    PRIVATE
        spdlog
        tinyxml2
)
