#include <stdexcept>
#include <cmath>

#include <misc/fixedString.h>
#include <misc/strLen.h>
#include <misc/minMax.h>

#pragma region constructors

FixedString::FixedString() : length(0), chars(new char[1])
{
    chars[0] = 0x00;
}
FixedString::FixedString(unsigned int _length) : length(_length), chars(new char[_length + 1])
{
    chars[length] = 0x00;
}
FixedString::FixedString(char* str)
{
    length = strLen(str);
    chars = new char[length + 1];

    for (unsigned int i = 0; i < length + 1; i++) chars[i] = str[i];
}
FixedString::FixedString(std::string str)
{
    length = (unsigned int)str.size();
    chars = new char[length + 1];

    for (unsigned int i = 0; i < length + 1; i++) chars[i] = str[i];
}
FixedString::~FixedString()
{ delete[] chars; }

#pragma endregion

char& FixedString::operator[](unsigned int i)
{
#if FIXED_STRING_ERROR_HANDLING

    if (i >= length) throw std::out_of_range("Index out of range");

#endif

    return chars[i];
}

char* FixedString::c_str()
{
    return chars;
}

#pragma region concat methods

FixedString FixedString::operator+(FixedString fs)
{
    FixedString proto(length + fs.length);

    unsigned int pos = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        proto[pos] = chars[i];

        pos++;
    }
    for (unsigned int i = 0; i < fs.length; i++)
    {
        proto[pos] = fs[i];

        pos++;
    }

    return proto;
}
FixedString FixedString::operator+(const char* str)
{ return *this + FixedString((char*)str); }
FixedString FixedString::operator+(char* str)
{ return *this + FixedString(str); }
FixedString FixedString::concat(FixedString fs)
{ return *this + fs; }
FixedString FixedString::concat(const char* str)
{ return *this + FixedString((char*)str); }
FixedString FixedString::concat(char* str)
{ return *this + FixedString(str); }

#pragma endregion

#pragma region insert methods

FixedString& FixedString::insert(FixedString fs, unsigned int pos)
{
#if FIXED_STRING_ERROR_HANDLING

    if (pos + fs.length > length - 1) throw std::out_of_range("Index is out of FixedString bounds");

#endif

    for (unsigned int i = 0; i < fs.length; i++)
    {
        chars[pos + i] = fs[i];
    }

    return *this;
}
FixedString& FixedString::insert(char* str, unsigned int pos)
{
#if FIXED_STRING_ERROR_HANDLING

    unsigned int strLength = strLen(str);

    if (pos + strLength > length - 1) throw std::out_of_range("Index is out of FixedString bounds");

    for (unsigned int i = 0; i < strLength; i++)
    {
        chars[pos + i] = str[i];
    }

#else

    for (unsigned int i = 0; str[i] != 0x00; i++)
    {
        chars[pos + i] = str[i];
    }

#endif

    return *this;
}

#pragma endregion

#pragma region toString methods

FixedString FixedString::toString(unsigned int num, unsigned int len)
{
    unsigned int numLength = (unsigned int)(log10(num) + 1);

    unsigned int protoLen = MAX(len, numLength);

    FixedString proto(protoLen);

    unsigned int remaining = num;

    for (unsigned int i = 0; i < numLength; i++)
    {
        proto[protoLen - i - 1] = (unsigned char)(remaining % 10 + 48);

        remaining /= 10;
    }
    for (unsigned int i = 0; i < protoLen - numLength; i++) proto[i] = 0x30;

    return proto;
}
FixedString FixedString::toString(unsigned int x)
{ return FixedString::toString(x, 0); }

#pragma endregion