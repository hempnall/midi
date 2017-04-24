#include <QFile>
#include <iostream>
#include <fstream>
#include "midi.h"
#include "midibulkdump.h"

#define MOXF_PATCH_PATH "/Users/jameshook/Music/moxf/bulkdumps"


void callback_func(const MidiSystemExclusiveMessage& sysex, void * userdata)
{
    std::cout << "Im being a callback \n";
    MidiBulkDump* bulkdump = static_cast<MidiBulkDump*>( userdata );
    if (bulkdump != nullptr) {
        bulkdump->addSysExMessage( &sysex.data()  );
    }
}


int main()
{

    midioutputs_t outs;
    std::cout << outs.size() << "\n";


    for (auto s : outs.portNames()) {
        std::cout << s << "\n";
    }


    try {

//        MidiBulkDump bulkdump;

//        MidiInputPort in_port(0);
//        in_port.setSysExCallback( callback_func , (void*) &bulkdump);
//        in_port.listen();
//        std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
//        char input;
//        std::cin.get(input);

//        QFile file( MOXF_PATCH_PATH "/bulktest.sysex"  );
//        file.open( QIODevice::WriteOnly );
//        QDataStream out(&file);
//        out << bulkdump;

        MidiBulkDump bulkdump;
        QFile file( MOXF_PATCH_PATH "/grandpiano.sysex"  );
        file.open( QIODevice::ReadOnly );
        QDataStream in(&file);
        in >> bulkdump;
        MidiOutputPort out_port(0);
        bulkdump.sendToMidiPort( out_port );

    } catch ( RtMidiError &error ) {

        error.printMessage();

    } catch (...) {

        std::cout << "this didn't work";

    }


    return 0;
}

