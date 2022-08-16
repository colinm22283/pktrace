#include <string>
#include <cmath>

#include <misc/misc.h>
#include <misc/getHex.h>
#include <misc/fixedString.h>
#include <misc/strLen.h>

#pragma region misc.h

bool Misc::isInt(std::string x)
{
    if (x.empty()) return false;
    for (int i = 0; i < (int)x.length(); i++) if (!std::isdigit(x[i]) || x[i] == '-') return false;
    return true;
}

#pragma endregion

#pragma region getHex.h

FixedString getHex(unsigned char num)
{
    FixedString proto(4);

    proto[0] = '0';
    proto[1] = 'x';

    for (unsigned char i = 2; i < 4; i++)
    {
        {
            unsigned char temp = (unsigned char) (num / pow(16, 3 - i   )) % 16;
            proto[i] = temp < 10 ? temp + 48 : temp + 55;
        }
    }

    return proto;
}

FixedString getHex(unsigned short num)
{
    FixedString proto(6);

    proto[0] = '0';
    proto[1] = 'x';

    for (unsigned char i = 2; i < 6; i++)
    {
        {
            unsigned char temp = (unsigned char) (num / pow(16, 5 - i   )) % 16;
            proto[i] = temp < 10 ? temp + 48 : temp + 55;
        }
    }

    return proto;
}

FixedString getHex(unsigned int num)
{
    FixedString proto(10);

    proto[0] = '0';
    proto[1] = 'x';

    for (unsigned char i = 2; i < 10; i++)
    {
        {
            unsigned char temp = (unsigned char) (num / pow(16, 9 - i   )) % 16;
            proto[i] = temp < 10 ? temp + 48 : temp + 55;
        }
    }

    return proto;
}

FixedString getHex(unsigned long num)
{
    FixedString proto(18);

    proto[0] = '0';
    proto[1] = 'x';

    for (unsigned char i = 2; i < 18; i++)
    {
        {
            unsigned char temp = (unsigned char) (num / pow(16, 17 - i   )) % 16;
            proto[i] = temp < 10 ? temp + 48 : temp + 55;
        }
    }

    return proto;
}

FixedString getHex(void* ptr)
{
    unsigned long num = reinterpret_cast<unsigned long>(ptr);

    FixedString proto(18);

    proto[0] = '0';
    proto[1] = 'x';

    for (unsigned char i = 2; i < 18; i++)
    {
        {
            unsigned char temp = (unsigned char) (num / pow(16, 17 - i   )) % 16;
            proto[i] = temp < 10 ? temp + 48 : temp + 55;
        }
    }

    return proto;
}

#pragma endregion

#pragma region strLen.h

unsigned int strLen(const char* str) { return strLen((char*)str); }
unsigned int strLen(char* str)
{
    unsigned int i;
    for (i = 0; str[i] != 0x00; i++);
    return i;
}

#pragma endregion