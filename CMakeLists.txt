cmake_minimum_required(VERSION 3.20)

project(PiUi VERSION 1.0.0 LANGUAGES CXX)

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

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("dependencies/GLFW")
set(GLFW_LIBRARY "glfw")
set_property(TARGET glfw PROPERTY FOLDER "PiUi/Dependencies/GLFW")
if (TARGET update_mappings)
	set_property(TARGET update_mappings PROPERTY FOLDER "PiUi/Dependencies/GLFW")
endif()

target_sources(PiUi PRIVATE
	"${SRC_DIR}/Main.cpp"
)

target_link_libraries(PiUi PRIVATE
	"${GLFW_LIBRARY}"
)
