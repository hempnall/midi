#include "midiinputport.h"
#include <vector>


void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
    MidiInputPort* port = static_cast<MidiInputPort*>(  userData );
    if (port != nullptr) {
        port->processMessage( deltatime , message);
    }
}

void MidiInputPort::setSysExCallback(sysexcallbackfunc_t fn)
{
    sysexcallback_ = fn;
}

void MidiInputPort::setModeMsgCallback(modemsgcallbackfunc_t fn)
{
    modecallback_ = fn;
}

void MidiInputPort::setVoiceMsgCallback(voicecallbackfunc_t fn)
{
    voicecallback_ = fn;
}

void MidiInputPort::listen()
{
    midiport_.setCallback( mycallback , (void*) this  );
    bool ignoreSysEx = ( sysexcallback_ == nullptr ) ;
    bool ignoreTiming = true;
    bool ignoreSensing = true;

    std::cout << std::boolalpha << "sysex=" << ignoreSysEx << " sensing=" << ignoreSensing << " ignoreTiming=" << ignoreTiming << "\n";

    midiport_.ignoreTypes(  ignoreSysEx ,  ignoreTiming ,  ignoreSensing  );
}

void MidiInputPort::processMessage(
        double deltatime,
        std::vector<unsigned char> *message)
{
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << deltatime << std::endl;
}



MidiInputPort::MidiInputPort()
    : sysexcallback_(nullptr),voicecallback_(nullptr),modecallback_(nullptr)
{}

MidiInputPort::MidiInputPort(int n)
    : MidiInputPort()
{
    midiport_.openPort(n);
}

MidiInputPort::MidiInputPort(const std::string &name)
    : MidiInputPort()
{
    midiport_.openVirtualPort(name);
}

MidiInputPort::~MidiInputPort()
{

}

void MidiInputPort::getInput()
{
    midiport_.setCallback( &mycallback );
    // Don't ignore sysex, timing, or active sensing messages.
    midiport_.ignoreTypes( false, true, true );
    std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
    char input;
    std::cin.get(input);
}



