#ifndef MIDIOUTPUTPORT_H
#define MIDIOUTPUTPORT_H


#include <RtMidi.h>

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
};

#endif // MIDIOUTPUTPORT_H
