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

void MidiOutputPort::sendMessage(mididatabuffer_t *msg)
{
    midiport_.sendMessage(msg);
}


