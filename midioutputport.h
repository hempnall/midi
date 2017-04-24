#ifndef MIDIOUTPUTPORT_H
#define MIDIOUTPUTPORT_H


#include <RtMidi.h>
#include "midisystemexclusivemessage.h"
#include "midichannelvoicemessage.h"
#include "midichannelmodemessage.h"

class MidiOutputPort
{
    RtMidiOut midiport_;

public:
    MidiOutputPort() = default;
    MidiOutputPort(int n);
    MidiOutputPort(  const std::string& name );
    ~MidiOutputPort();

    void noteOn(int key,int vel);
    void noteOff(int key);
    void getOutput();
    void sendMessage( mididatabuffer_t *msg );
};

#endif // MIDIOUTPUTPORT_H
