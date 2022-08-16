#pragma once

#include <string>

#include <misc/fixedString.h>

FixedString getHex(unsigned char num);
FixedString getHex(unsigned short num);
FixedString getHex(unsigned int num);
FixedString getHex(unsigned long num);
FixedString getHex(void* ptr);