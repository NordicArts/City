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
set(Game ${NOS}/Game)
link_directories(${Game})
include_directories(${Game})
list(APPEND GameSources ${Game}/Game.cpp)
list(APPEND GameHeaders ${Game}/Game.hpp)

# Game State
link_directories(${Game}/GameState)
include_directories(${Game}/GameState)
list(APPEND GameHeaders ${Game}/GameState.hpp)
list(APPEND GameSources ${Game}/GameState/Editor.cpp)
list(APPEND GameHeaders ${Game}/GameState/Editor.hpp)
list(APPEND GameSources ${Game}/GameState/Start.cpp)
list(APPEND GameHeaders ${Game}/GameState/Start.hpp)

# Engine (mainly for include management)
set(Engine ${NOS}/Engine)
link_directories(${Engine})
include_directories(${Engine})

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

# GUI
link_directories(${Engine}/GUI)
include_directories(${Engine}/GUI)
list(APPEND GameSources ${Engine}/GUI/Style.cpp)
list(APPEND GameHeaders ${Engine}/GUI/Style.hpp)
list(APPEND GameSources ${Engine}/GUI/Entry.cpp)
list(APPEND GameHeaders ${Engine}/GUI/Entry.hpp)
list(APPEND GameSources ${Engine}/GUI/GUI.cpp)
list(APPEND GameHeaders ${Engine}/GUI/GUI.hpp)
list(APPEND GameHeaders ${Engine}/GUI.hpp)

# Map
link_directories(${Game}/Map)
include_directories(${Game}/Map)
list(APPEND GameSources ${Game}/Map/Map.cpp)
list(APPEND GameHeaders ${Game}/Map/Map.hpp)

# City
link_directories(${Game}/City)
include_directories(${Game}/City)
list(APPEND GameSources ${Game}/City/City.cpp)
list(APPEND GameHeaders ${Game}/City/City.hpp)

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


