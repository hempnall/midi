#include "midisystemexclusivemessage.h"

#include <iostream>

MidiSystemExclusiveMessage::MidiSystemExclusiveMessage()
{

}

MidiSystemExclusiveMessage::~MidiSystemExclusiveMessage()
{

}

void MidiSystemExclusiveMessage::readMessage(mididatabuffer_t *message)
{
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    std::cout << "\n";
}

