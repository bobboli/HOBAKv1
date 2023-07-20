cmake_minimum_required(VERSION 3.23)
project(hobak)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# About the quote marks in CMake:
# https://crascit.com/2022/01/25/quoting-in-cmake/


list(APPEND CMAKE_PREFIX_PATH "../../ext/freeglut")
find_package(GLUT REQUIRED)

# Add your project files
set(INC_DIR "./" "../" "../../" "../../ext/eigen-3.3.7" "../../src/" "../../src/util" "../../ext/spectra-0.8.1/include" "../../ext/rapidjson" "../../ext/glvu/" "../../ext/rapidjson/")

# Create an empty list variable to store all the files
set(INC_FILES)

# Loop through each directory and add files to the ALL_FILES variable
foreach(dir ${INC_DIR})
    file(GLOB dir_files "${dir}/*.h")
    list(APPEND INC_FILES ${dir_files})
endforeach()


file(GLOB SRC_FILES 
simulateScene.cpp
../../ext/glvu/glvu.cpp
../../src/util/MATRIX_UTIL.cpp
../../src/util/COLLISION_UTIL.cpp
../../src/util/FILE_IO.cpp
../../src/util/TIMER.cpp
../../src/util/DRAW_GL.cpp
../../src/Timestepper/BACKWARD_EULER_VELOCITY.cpp
../../src/Timestepper/BACKWARD_EULER_POSITION.cpp
../../src/Timestepper/TIMESTEPPER.cpp
../../src/Timestepper/BDF_1.cpp
../../src/Timestepper/BDF_2.cpp
../../src/Timestepper/NEWMARK.cpp
../../src/Timestepper/QUASISTATIC.cpp
../../src/Geometry/LINE_INTERSECT.cpp
../../src/Geometry/CAPSULE.cpp
../../src/Geometry/CYLINDER.cpp
../../src/Geometry/CUBE.cpp
../../src/Geometry/SPHERE.cpp
../../src/Geometry/AABB_TREE.cpp
../../src/Geometry/TET_MESH.cpp
../../src/Geometry/TET_MESH_FASTER.cpp
../../src/Damping/Volume/GREEN_DAMPING.cpp
../../src/Hyperelastic/Volume/EDGE_COLLISION.cpp
../../src/Hyperelastic/Volume/EDGE_SQRT_COLLISION.cpp
../../src/Hyperelastic/Volume/EDGE_HYBRID_COLLISION.cpp
../../src/Hyperelastic/Volume/MCADAMS_COLLISION.cpp
../../src/Hyperelastic/Volume/VERTEX_FACE_COLLISION.cpp
../../src/Hyperelastic/Volume/VERTEX_FACE_SQRT_COLLISION.cpp
../../src/Hyperelastic/Volume/ANISOTROPIC_ARAP.cpp
../../src/Hyperelastic/Volume/ANISOTROPIC_STVK.cpp
../../src/Hyperelastic/Volume/ANISOTROPIC_FUNG.cpp
../../src/Hyperelastic/Volume/ANISOTROPIC_DIRICHLET.cpp
../../src/Hyperelastic/Volume/STVK.cpp
../../src/Hyperelastic/Volume/SNH.cpp
../../src/Hyperelastic/Volume/LINEAR.cpp
../../src/Hyperelastic/Volume/ARAP.cpp
../../src/Hyperelastic/Volume/HYPERELASTIC.cpp
)

add_executable(${PROJECT_NAME}
	${SRC_FILES}
	${INC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLUT_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} ${GLUT_glut_LIBRARY})
# It's annoying that CMake cannot deal with x86 or x64 lib. Set them manually.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Building for x64 (64-bit)")
    set(FREEGLUT_LIB "${CMAKE_SOURCE_DIR}/../../ext/freeglut/lib/x64/freeglut.lib")
    set(FREEGLUT_DLL "${CMAKE_SOURCE_DIR}/../../ext/freeglut/bin/x64/freeglut.dll")
else()
    message(STATUS "Building for x86 (32-bit)")
    set(FREEGLUT_LIB "${CMAKE_SOURCE_DIR}/../../ext/freeglut/lib/freeglut.lib")
    set(FREEGLUT_DLL "${CMAKE_SOURCE_DIR}/../../ext/freeglut/bin/freeglut.dll")
endif()
target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIB})
# Set the output directory for the executable
set(BIN_DIR "${CMAKE_SOURCE_DIR}/../../bin")
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR} # Change this to your desired output directory
)

# Copy the dll next to exe... That lib is only an import library.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
${FREEGLUT_DLL}
$<TARGET_FILE_DIR:${PROJECT_NAME}>)