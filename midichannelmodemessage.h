#ifndef MIDICHANNELMODEMESSAGE_H
#define MIDICHANNELMODEMESSAGE_H


#include "midichannelmessage.h"

class MidiChannelModeMessage : public virtual MidiChannelMessage
{
public:
    MidiChannelModeMessage();
    ~MidiChannelModeMessage();
};

#endif // MIDICHANNELMODEMESSAGE_H
