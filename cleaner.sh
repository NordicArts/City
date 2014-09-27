#!/bin/bash

rm -rf Build

# Delete CMake Stuff
rm -rf `find . -type d -name CMakeFiles`
rm -rf `find . -type d -name build`
rm -rf `find . -type f -name CMakeCache.txt`
rm -rf `find . -type f -name Makefile`
rm -rf `find . -type f -name cmake_install.cmake`

# Delete old libraries
rm -rf `find . -type f -name libGame.a`
rm -rf `find . -type f -name libValkyrie.a`
rm -rf `find . -type f -name libValkyrieEngine.a`
rm -rf `find . -type f -name libThirdPartyLibs.a`
rm -rf `find . -type f -name libGameLibrary.a`
rm -rf `find . -type f -name libSQLite.a`
rm -rf `find . -type f -name libNordicOS.a`


# Delete Binary
rm -rf `find . -type f -name City.app`
rm -rf `find . -type f -name City.log`

mkdir Build
cd Build
touch empty
