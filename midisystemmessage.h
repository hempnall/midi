#ifndef MIDISYSTEMMESSAGE_H
#define MIDISYSTEMMESSAGE_H

#include "midimessage.h"

class MidiSystemMessage : public virtual MidiMessage
{
public:
    MidiSystemMessage();
    virtual ~MidiSystemMessage() = default;
};

#endif // MIDISYSTEMMESSAGE_H
