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
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
)

# glm
add_subdirectory("dependencies/glm")

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("dependencies/glfw")
set(GLFW_LIBRARY "glfw")
set_property(TARGET glfw PROPERTY FOLDER "Junia/Dependencies/GLFW")
if (TARGET update_mappings)
	set_property(TARGET update_mappings PROPERTY FOLDER "Junia/Dependencies/GLFW")
endif()

target_sources(PiUi PRIVATE
	"${SRC_DIR}/FileSystem.cpp"
	"${SRC_DIR}/Gamecontroller.cpp"
	"${SRC_DIR}/Main.cpp"
	"${SRC_DIR}/Material.cpp"
	"${SRC_DIR}/Quad.cpp"

	"${SRC_DIR}/opengl.c"
)

target_include_directories(PiUi PRIVATE
	"${DEPENDENCIES_DIR}/glm/"
	"${DEPENDENCIES_DIR}/glfw/include/"
)

target_link_libraries(PiUi PRIVATE
	"glm"
	"GLESv2"
	"${GLFW_LIBRARY}"
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
