#include "midichannelmessage.h"

MidiChannelMessage::MidiChannelMessage()
    : channel_(0)
{

}

int MidiChannelMessage::channel()
{
    return channel_;
}

