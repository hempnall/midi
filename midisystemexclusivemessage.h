#ifndef MIDISYSTEMEXCLUSIVEMESSAGE_H
#define MIDISYSTEMEXCLUSIVEMESSAGE_H

#include "midisystemmessage.h"

class MidiSystemExclusiveMessage : public virtual MidiSystemMessage
{
    mididatabuffer_t bufferdata_;

public:
    MidiSystemExclusiveMessage();
    ~MidiSystemExclusiveMessage();

    void readMessage( mididatabuffer_t *message );
    const mididatabuffer_t &data() const;
};

#endif // MIDISYSTEMEXCLUSIVEMESSAGE_H
