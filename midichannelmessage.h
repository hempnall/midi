#ifndef MIDICHANNELMESSAGE_H
#define MIDICHANNELMESSAGE_H

#include "midimessage.h"

class MidiChannelMessage : public virtual MidiMessage
{
    int channel_;

public:
    MidiChannelMessage();
    virtual ~MidiChannelMessage() = default;
    int channel();
};

#endif // MIDICHANNELMESSAGE_H
