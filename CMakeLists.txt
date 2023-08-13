cmake_minimum_required(VERSION 3.10)

project(PiUi VERSION 1.0.0 LANGUAGES CXX C)

add_executable(PiUi)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/PiUi")

set_target_properties(PiUi PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_STANDARD 20
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Debug"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Release"
	RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
)

# glm
add_subdirectory("dependencies/glm")

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("dependencies/GLFW")
set(GLFW_LIBRARY "glfw")

target_sources(PiUi PRIVATE
	"${SRC_DIR}/FileSystem.cpp"
	"${SRC_DIR}/Gamecontroller.cpp"
	"${SRC_DIR}/Gamepad.cpp"
	"${SRC_DIR}/Main.cpp"
	"${SRC_DIR}/Material.cpp"
	"${SRC_DIR}/Quad.cpp"

	"${SRC_DIR}/opengl.c"
)

target_include_directories(PiUi PRIVATE
	"${DEPENDENCIES_DIR}/glm/"
)

target_link_libraries(PiUi PRIVATE
	"${GLFW_LIBRARY}"
	"glm"
)

add_custom_target(PiUiResources
	${CMAKE_COMMAND} -E remove_directory
		"${OUTPUT_DIR}/$<CONFIG>/res"
	COMMAND ${CMAKE_COMMAND} -E make_directory
		"${OUTPUT_DIR}/$<CONFIG>/res"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${RES_DIR}/background.vert.glsl"
		"${RES_DIR}/background.frag.glsl"
		"${OUTPUT_DIR}/$<CONFIG>/res/"
	COMMENT "Copying resource files for PiUi" VERBATIM
	SOURCES
		"${RES_DIR}/background.vert.glsl"
		"${RES_DIR}/background.frag.glsl"
)

add_dependencies(PiUi PiUiResources)

if (WIN32)

target_sources(PiUi PRIVATE
	"${DEPENDENCIES_DIR}/glad/src/glad.c"
)

target_include_directories(PiUi PRIVATE
	"${DEPENDENCIES_DIR}/glad/include/"
)

endif (WIN32)

if (UNIX)

target_link_libraries(PiUi PRIVATE
	"GLESv2"
)

endif (UNIX)
