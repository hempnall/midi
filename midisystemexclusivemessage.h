#ifndef MIDISYSTEMEXCLUSIVEMESSAGE_H
#define MIDISYSTEMEXCLUSIVEMESSAGE_H

#include "midisystemmessage.h"

class MidiSystemExclusiveMessage : public virtual MidiSystemMessage
{
public:
    MidiSystemExclusiveMessage();
    ~MidiSystemExclusiveMessage();
};

#endif // MIDISYSTEMEXCLUSIVEMESSAGE_H
