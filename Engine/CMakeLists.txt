cmake_minimum_required(VERSION 3.6)

# Project Name
PROJECT(engine)

if (NOT APPLE)
    if (WIN32)
        set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
        include_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
        link_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
    else(WIN32)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    find_package(DevIL REQUIRED)
    link_libraries(${IL_LIBRARIES} )
    include_directories(ยง{IL_INCLUDE_DIR})
endif(NOT WIN32)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_executable(${PROJECT_NAME} engine.cpp parser.cpp include/pugixml.cpp Group.cpp Group.h catmull-rom.h catmull-rom.cpp Model.cpp Model.h Light.cpp Light.h texture.cpp texture.h)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32 DevIL)
    file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})

else(WIN32)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif (WIN32)

file(COPY exemplos/plane.3d DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/plane.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/box.3d DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/box.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/cone.3d DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/cone.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/sphere.3d DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/sphere.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/SistemaSolar.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY exemplos/teapot.3d DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/sun.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/mercury.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/venus.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/earth.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/mars.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/jupiter.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/saturn.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/uranus.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures/neptune.jpg DESTINATION ${CMAKE_BINARY_DIR})
