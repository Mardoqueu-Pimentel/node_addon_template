cmake_minimum_required(VERSION 3.14)
project(project)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(node_modules/node-addon-api)
include_directories(node_modules/node-addon-api/external-napi)

add_subdirectory(addon/template)
