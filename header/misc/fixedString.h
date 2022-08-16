#pragma once

#include <string>

#ifndef FIXED_STRING_ERROR_HANDLING
#define FIXED_STRING_ERROR_HANDLING 1
#endif

class FixedString
{
public:
    FixedString();
    FixedString(unsigned int length);
    FixedString(char* str);
    FixedString(std::string str);
    ~FixedString();

    char& operator[](unsigned int i);

    char* c_str();

    FixedString operator+(FixedString fs);
    FixedString operator+(const char* str);
    FixedString operator+(char* str);
    FixedString concat(FixedString fs);
    FixedString concat(const char* str);
    FixedString concat(char* str);

    FixedString& insert(FixedString fs, unsigned int pos);
    FixedString& insert(char* str, unsigned int pos);

    // TODO: add more toString methods
    static FixedString toString(unsigned int x, unsigned int len);
    static FixedString toString(unsigned int x);
private:
    unsigned int length;
    char* chars;
};