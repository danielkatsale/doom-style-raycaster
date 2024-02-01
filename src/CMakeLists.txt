cmake_minimum_required(VERSION 3.10)
project(simple_ray_caster_opengl)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find the required packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Include the header files
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Define your executable
add_executable(simple_ray_caster_opengl main.c)

# Link the libraries with your executable
target_link_libraries(simple_ray_caster_opengl OpenGL glfw GLEW m)

