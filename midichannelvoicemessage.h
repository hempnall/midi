#ifndef MIDICHANNELVOICEMESSAGE_H
#define MIDICHANNELVOICEMESSAGE_H

#include "midichannelmessage.h"

class MidiChannelVoiceMessage : public virtual MidiChannelMessage
{
public:
    MidiChannelVoiceMessage();
    ~MidiChannelVoiceMessage();
};

#endif // MIDICHANNELVOICEMESSAGE_H
