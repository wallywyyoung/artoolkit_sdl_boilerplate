cmake_minimum_required(VERSION 3.4)
project(ARTOOLKIT_BOILERPLATE)

#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    # OS X
#    set(PLATFORM_CXX_FLAGS "-framework OpenGL")
#
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    # Linux
#    set(PLATFORM_CXX_FLAGS "-lGL")
#endif()

find_package(OpenGL REQUIRED)
find_library(SDL2_LIBRARY SDL2)
find_library(SDL2main_LIBRARY SDL2main)
#find_library(GLEW_LIBRARY GLEW)
set(LIBRARIES ${SDL2_LIBRARY} ${SDL2main_LIBRARY} ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
else()
    message("ERROR! GLEW NOT FOUND")
endif()


include_directories(${OPENGL_INCLUDE_DIRS})





#file(READ "Shaders/simple.frag" SIMPLE_FRAG)
#string(REGEX REPLACE " " "\\\\ " SIMPLE_FRAG ${SIMPLE_FRAG})

#file(READ "Shaders/simple.vert" SIMPLE_VERT)
#message(${SIMPLE_FRAG})
#add_definitions(-DSIMPLE_FRAG="\"R\(\"${SIMPLE_FRAG}\"\)\"" -DSIMPLE_VERT=${SIMPLE_VERT})
#add_definitions(-DSIMPLE_FRAG=R\(\"${SIMPLE_FRAG}\"\))
#add_definitions(-DSIMPLE_VERT=\"bar\")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    sdl_template.c)

add_executable(ARTOOLKIT_BOILERPLATE ${SOURCE_FILES})

target_link_libraries(ARTOOLKIT_BOILERPLATE ${LIBRARIES})
