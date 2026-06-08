cmake_minimum_required(VERSION 3.23)
project(VulkanSandbox)

# Set C++ version to 23 and statically link MSVC library
Set(CMAKE_CXX_STANDARD 23)
Set(CMAKE_CXX_STANDARD_REQUIRED ON)
Set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Turn on optimizations for productions builds
Set(PRODUCTION_BUILD "Enable production optimizations" ON)
if(PRODUCTION_BUILD)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	

# Ensure GLFW statically links
Set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
Set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
Set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
Set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


# Load library paths
add_subdirectory("lib/glfw-3.4")
add_subdirectory("lib/GLM")

find_package(Vulkan REQUIRED)

# include all files into the project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(VulkanSandbox ${MY_SOURCES})
target_include_directories(VulkanSandbox PRIVATE src)

# Link libraries
target_link_libraries(VulkanSandbox PRIVATE glfw Vulkan::Vulkan glm)

# Enable compiler warnings
if(MSVC)
    target_compile_options(VulkanSandbox PRIVATE /W4 /permissive-)
else()
    target_compile_options(VulkanSandbox PRIVATE -Wall -Wextra -Wpedantic)
endif()