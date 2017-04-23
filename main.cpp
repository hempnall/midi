#include <iostream>
#include <fstream>
#include "midi.h"

using namespace std;

#define MOXF_PATCH_PATH "/Users/jameshook/Music/moxf/bulkdumps"


void callback_func(const MidiSystemExclusiveMessage& sysex)
{
    cout << "Im being a callback \n";
}


int main()
{

    midioutputs_t outs;
    cout << outs.size() << "\n";


    for (auto s : outs.portNames()) {
        cout << s << "\n";
    }


    try {

        MidiInputPort in_port(0);
        in_port.setSysExCallback( callback_func );
        in_port.listen();
        std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
        char input;
        std::cin.get(input);

    } catch ( RtMidiError &error ) {

        error.printMessage();

    } catch (...) {

        std::cout << "this didn't work";

    }


    return 0;
}

