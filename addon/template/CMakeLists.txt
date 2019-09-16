cmake_minimum_required(VERSION 3.14)

project(template VERSION 1.0.0 LANGUAGES CXX)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options (-fcolor-diagnostics)
endif ()

set(TARGET_ADDON ${PROJECT_NAME})
set(HEADERS_PATH ${PROJECT_SOURCE_DIR}/include/template)
set(TARGET_ADDON_HEADERS
	${HEADERS_PATH}/binding.hpp
	${HEADERS_PATH}/type.hpp
	${HEADERS_PATH}/util.hpp
	${HEADERS_PATH}/Worker.hpp
	${HEADERS_PATH}/Klass.hpp
)
set(SOURCES_PATH ${PROJECT_SOURCE_DIR}/src)
set(TARGET_ADDON_SOURCES
	${SOURCES_PATH}/binding.cpp
	${SOURCES_PATH}/util.cpp
	${SOURCES_PATH}/Worker.cpp
	${SOURCES_PATH}/Klass.cpp
)
add_library(${TARGET_ADDON} SHARED ${TARGET_ADDON_HEADERS} ${TARGET_ADDON_SOURCES})
target_include_directories(${TARGET_ADDON}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(lib/mardcpp)

target_link_libraries(${TARGET_ADDON} mardcpp)

set_target_properties(${TARGET_ADDON} PROPERTIES
	PREFIX ""
	SUFFIX ".node"
	CXX_STANDARD 17
)

if (MSVC)
	target_compile_options(${TARGET_ADDON}
		PRIVATE /W4 /WX
	)
else()
	target_compile_options(${TARGET_ADDON}
		PRIVATE -Wall -Wextra -pedantic -m64 -pthread -MMD -m64 -fno-omit-frame-pointer -fno-rtti
	)
endif()

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
	target_link_libraries(${TARGET_ADDON} OpenMP::OpenMP_CXX)
endif()