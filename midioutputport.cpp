#include "midioutputport.h"
#include <iostream>


MidiOutputPort::MidiOutputPort(int n)
{
    midiport_.openPort(n);
}

MidiOutputPort::MidiOutputPort(const std::string &name)
{
    midiport_.openVirtualPort(name);
}

MidiOutputPort::~MidiOutputPort()
{

}


void MidiOutputPort::noteOn(int key, int vel)
{
    std::vector< unsigned char >  	message(3);
    message[0] = 0x90;
    message[1] = 64;
    message[2] = 90;
    midiport_.sendMessage( &message );

}

void MidiOutputPort::noteOff(int key)
{

}

void MidiOutputPort::getOutput()
{

    std::cout << "\nReading MIDI output ... press <enter> to quit.\n";
    char input;
    std::cin.get(input);
}


