#pragma once

#include "config.h"

#if PEAK_ENGINE_DEBUG_MODE

#include <iostream>

#define debugPrint(message) std::cout<<"\033[34m"<<message<<"\033[0m\n"
#define debugWarn(message) std::cout<<"\033[33m"<<__FILE__<<" line "<< __LINE__ <<": "<<message<<"\033[0m\n"
#define debugError(message) std::cout<<"\033[31m"<<__FILE__<<" line "<< __LINE__ <<": "<<message<<"\033[0m\n"

#else

#define debugPrint(message)
#define debugError(message)

#endif