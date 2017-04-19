#ifndef MIDI_H
#define MIDI_H


#include <vector>
#include <string>
#include <algorithm>
#include "midiinputport.h"
#include "midioutputport.h"

template<typename T>
class Midi
{
    T midiport_ ;

    std::string get_port_name(int index) {
        if ( index >=0 && index < size() ) {
            return midiport_.getPortName(index);
        } else {
            return 0;
        }
    }

public:

    int size() {
        return midiport_.getPortCount();
    }

    std::vector<std::string> portNames() {

        std::vector< std::string > ret_val( size() );

        for (int i=0 ; i < size() ; ++i ) {
            ret_val[i] = get_port_name(i);
        }

        return ret_val;

    }

    MidiInputPort openInput(int n) {
        return MidiInputPort(n);
    }

    MidiOutputPort openOutput(int n) {
        return MidiOutputPort(n);
    }

};

typedef Midi<RtMidiIn>  midiinputs_t;
typedef Midi<RtMidiOut> midioutputs_t;



#endif // MIDI_H
