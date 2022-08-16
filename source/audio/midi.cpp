#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <debug.h>

#include <misc/list.h>

#include <audio/midi.h>

unsigned int readUVariableLength(std::ifstream* file)
{
    unsigned char bufferLen;
    unsigned char buffer[sizeof(unsigned int)];

    for (bufferLen = 0; bufferLen < sizeof(unsigned int); bufferLen++)
    {
        file->read(reinterpret_cast<char*>(buffer + bufferLen), sizeof(unsigned char));

        if ((buffer[bufferLen] & 0x80) == 0)
        {
            bufferLen++;
            break;
        }
    }

    unsigned int proto = 0;

    for (unsigned int i = 0; i < bufferLen; i++)
    {
        proto += (unsigned int)(buffer[i] & 0x7F) * pow(128, bufferLen - i - 1);
    }

    return proto;
}
unsigned int readUInt32(std::ifstream* file)
{
    unsigned char buffer[4];
    file->read(reinterpret_cast<char*>(buffer), sizeof(unsigned char) * 4);
    return (unsigned int)buffer[3] | (unsigned int)buffer[2] << 8 | (unsigned int)buffer[1] << 16 | (unsigned int)buffer[0] << 24;
}
unsigned short readUInt16(std::ifstream* file)
{
    unsigned char buffer[2];
    file->read(reinterpret_cast<char*>(buffer), sizeof(unsigned char) * 2);
    return (unsigned short)buffer[1] | (unsigned short)buffer[0] << 8;
}
unsigned char readUInt8(std::ifstream* file)
{
    unsigned char buffer;
    file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
    return buffer;
}

MIDI::MIDI()
{
    deltaTime = 0;
    stepCount = 0;
    steps = nullptr;
}
MIDI::MIDI(unsigned int length, unsigned short _deltaTime)
{
    deltaTime = _deltaTime;
    stepCount = length;
    steps = new midiStep[length];
    for (unsigned int i = 0; i < length; i++)
    {
        steps[i].noteCount = 2;
        steps[i].notes = new midiNote[2];
        steps[i].notes[0].pitch = i * 50 + 50;
        steps[i].notes[1].pitch = i * 50 + 100;
        steps[i].notes[0].length = 1000;
        steps[i].notes[1].length = 1000;
    }
}

MIDI::MIDI(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) throw std::errc::no_such_file_or_directory;

    file.seekg(10);

    unsigned short trackCount = readUInt16(&file);
    debugPrint("Track count: " << trackCount);

    deltaTime = readUInt16(&file);
    debugPrint("Delta time: " << deltaTime);

    file.seekg(18);

    unsigned int trackSize = readUInt32(&file);
    debugPrint("Track length: " << trackSize);

    List<midiStep> s;
    for (unsigned int i = 0; i < trackSize; i++)
    {
        debugPrint("EVENT");

        unsigned int time = readUVariableLength(&file);
        debugPrint("  Time: " << time);

        switch (readUInt8(&file))
        {
            case 0xFF: //                                                                          META EVENT
            {
                debugPrint("  META EVENT");

                unsigned char eventType = readUInt8(&file);
                unsigned int length = readUVariableLength(&file);

                switch (eventType)
                {
                    case 0x03: // Sequence/track name
                    {
                        debugPrint("    Type: Sequence/track name");

                        char* name = new char[length];

                        for (unsigned int j = 0; j < length; j++) name[j] = readUInt8(&file);

                        debugPrint("    Name: " << name);

                        delete[] name;
                    } break;
                    default:
                    {
                        file.seekg((unsigned int)file.tellg() + length);
                    } break;
                }
            } break;
            case 0xF0:  //                                                                         SYSTEM EVENT
            case 0xF7:
            {
                debugPrint("  SYSTEM EVENT");

                unsigned char temp;
                do temp = readUInt8(&file);
                while (temp != 0xF7);
            } break;
            default: //                                                                            MIDI EVENT
            {
                debugPrint("  MIDI EVENT");

                file.seekg((unsigned int)file.tellg() - 1);

                unsigned char status = readUInt8(&file);

                unsigned char event = status & 0xF0;
//                unsigned char channel = status & 0x0F;

                switch (event)
                {
                    case 0x08:
                        debugPrint("    Note off");

                        s.push({
                            1,
                           new midiNote[1] {
                                   { readUInt8(&file), readUInt8(&file) }
                            }
                        });
                        break;
                    case 0x09:
                        debugPrint("    Note on");
                        break;
                }
            } break;
        }
    }

    file.close();
}
MIDI::~MIDI()
{
    for (unsigned int i = 0; i < stepCount; i++)
    {
        delete[] steps[i].notes;
    }
    delete[] steps;
}