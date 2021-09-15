cmake_minimum_required(VERSION 3.3.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# define name
set(PROJECT_NAME_SHORT "CO")

# set the project name
project("CreatureOasis" VERSION 1.0)

##############
# Executable
##############
add_executable(${PROJECT_NAME} main.cpp)

configure_file(CreatureOasisConfig.h.in CreatureOasisConfig.h)

set(OGRE_DIR Dependencies/Ogre/sdk/CMake)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
 
# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(${PROJECT_NAME} OgreBites OgreRTShaderSystem)

target_include_directories(${PROJECT_NAME} PUBLIC 
                        "${PROJECT_BINARY_DIR}")