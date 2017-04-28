#include <QFile>
#include <iostream>
#include <fstream>
#include "midi.h"
#include "midibulkdump.h"
#include <fstream>

#define MOXF_PATCH_PATH "/Users/jameshook/Music/moxf/bulkdumps"


void callback_func(const MidiSystemExclusiveMessage& sysex, void * userdata)
{
    std::cout << "Im being a callback \n";
    MidiBulkDump* bulkdump = static_cast<MidiBulkDump*>( userdata );
    if (bulkdump != nullptr) {
        bulkdump->addSysExMessage( &sysex.data()  );
    }
}


void read_bulk_dump_data() {
    MidiBulkDump new_bulkdump;
    MidiInputPort in_port(0);
    in_port.setSysExCallback( callback_func , (void*) &new_bulkdump);
    in_port.listen();
    std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
    char input;
    std::cin.get(input);
    std::ofstream ofs( MOXF_PATCH_PATH "/test21");
    boost::archive::text_oarchive oa(ofs);
    oa << new_bulkdump;
}


void write_bulk_data_dump() {
    MidiBulkDump bulkdump;
    std::ifstream ifs( MOXF_PATCH_PATH "/test21" );
    boost::archive::text_iarchive ia(ifs);

    ia >> bulkdump;

    MidiOutputPort out_port(0);
    bulkdump.sendToMidiPort( out_port );
}

int main()
{

    try {

        write_bulk_data_dump();


    } catch ( RtMidiError &error ) {

        error.printMessage();

    } catch (...) {

        std::cout << "this didn't work";

    }


    return 0;
}

