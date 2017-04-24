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
    bufferdata_ = mididatabuffer_t( message->begin() , message->end()  );
}

const mididatabuffer_t &MidiSystemExclusiveMessage::data() const
{
    return bufferdata_;
}

