#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include <vector>

typedef std::vector< unsigned char > mididatabuffer_t;

class MidiMessage
{
public:
    MidiMessage();
    virtual ~MidiMessage() = default;
};

#endif // MIDIMESSAGE_H
