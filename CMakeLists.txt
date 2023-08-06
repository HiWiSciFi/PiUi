cmake_minimum_required(VERSION 3.20)

project(PiUi VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory("dependencies")

add_executable(PiUi)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/PiUi")

set_target_properties(PiUi PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_STANDARD 20
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Debug"
	RUNTIME_OUTPUT_DIRECTIRY_RELEASE "${OUTPUT_DIR}/Release"
	FOLDER "PiUi"
)

target_sources(PiUi PRIVATE
	"${SRC_DIR}/Main.cpp"
)
