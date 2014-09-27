# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(City)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# Output Dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build)

# Set Source
set(NOS ${PROJECT_SOURCE_DIR}/City)
set(GameSources ${NOS}/Main/Main.cpp)
set(GameHeaders ${NOS}/Main/Main.hpp)

# Game
link_directories(${NOS}/Game)
include_directories(${NOS}/Game)
list(APPEND GameSources ${NOS}/Game/Game.cpp)
list(APPEND GameHeaders ${NOS}/Game/Game.hpp)

# Game State
link_directories(${NOS}/Game/GameState)
include_directories(${NOS}/Game/GameState)
list(APPEND GameHeaders ${NOS}/Game/GameState.hpp)
list(APPEND GameSources ${NOS}/Game/GameState/Editor.cpp)
list(APPEND GameHeaders ${NOS}/Game/GameState/Editor.hpp)
list(APPEND GameSources ${NOS}/Game/GameState/Start.cpp)
list(APPEND GameHeaders ${NOS}/Game/GameState/Start.hpp)

# Engine (mainly for include management)
link_directories(${NOS}/Engine)
include_directories(${NOS}/Engine)
set(Engine ${NOS}/Engine)

# Animation
link_directories(${Engine}/Animation)
include_directories(${Engine}/Animation)
list(APPEND GameHeaders ${Engine}/Animation.hpp)
list(APPEND GameSources ${Engine}/Animation/Animation.cpp)
list(APPEND GameHeaders ${Engine}/Animation/Animation.hpp)
list(APPEND GameSources ${Engine}/Animation/Handler.cpp)
list(APPEND GameHeaders ${Engine}/Animation/Handler.hpp)

# Texture
link_directories(${Engine}/Texture)
include_directories(${Engine}/Texture)
list(APPEND GameHeaders ${Engine}/Texture.hpp)
list(APPEND GameSources ${Engine}/Texture/Manager.cpp)
list(APPEND GameHeaders ${Engine}/Texture/Manager.hpp)

# Tile
link_directories(${Engine}/Tile)
include_directories(${Engine}/Tile)
list(APPEND GameSources ${Engine}/Tile/Tile.cpp)
list(APPEND GameHeaders ${Engine}/Tile/Tile.hpp)

# SFML
find_package(SFML REQUIRED system window graphics audio network)
include_directories(${SFML_INCLUDE_DIR})

# Compile
add_executable(City ${GameSources} ${GameHeaders})
set_target_properties(City PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(City PROPERTIES OUTPUT_NAME "City.app")
set_target_properties(City PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS}) 

# Link
target_link_libraries(City "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit")
target_link_libraries(City ${SFML_LIBRARIES})


