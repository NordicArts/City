#ifndef NordicArts_City_Main_H
#define NordicArts_City_Main_H

// Includes
#include <cassert> // Asserts
#include <time.h> // Time
#include <ctime> // Time
#include <iostream> // Input-Output stream
#include <string> // Strings
#include <string.h> // Strings
#include <stdexcept> // Excepetions
#include <cmath> // Maths
#include <fstream> // Streams
#include <sstream> // Streams
#include <vector> // Vector Array
#include <cstddef> // Standard Defs
#include <stdlib.h> // STD lib
#include <stdio.h> // STD input-Output
#include <cstring> // Strings
#include <list> // List Array
#include <stdarg.h> // STD Arguments
#include <stdint.h> // STD integer
#include <array> // Array
#include <iomanip> // Input-Output Manipulation
#include <math.h> // Math
#include <algorithm> // Misc
#include <unordered_map> // Unordered Map
#include <map> // Map
#include <ios> // Some standard input-output

// OSX Includes
#ifdef __OBJC__    
    #import <Cocoa/Cocoa.h>
    #import <Foundation/Foundation.h>
    #import <CoreFoundation/CoreFoundation.h>
#endif

// Errors
#ifndef printStuff
#define printStuff
#define printIt(variable) { std::cout << #variable << " " << variable << std::endl; }
#endif

namespace NordicArts {
    int main();
};

#endif
