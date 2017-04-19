#include <iostream>
#include "midi.h"

using namespace std;

int main()
{

    midioutputs_t outs;
    cout << outs.size() << "\n";


    for (auto s : outs.portNames()) {
        cout << s << "\n";
    }


    try {

        sysexcallbackfunc_t dn = (sysexcallbackfunc_t) &outs;

        MidiInputPort in_port(0);
        in_port.setSysExCallback( dn );
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

