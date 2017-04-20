#include "midiinputport.h"
#include <vector>

#define DEBUG( x , y ) std::cout << "[DEBUG] channel: " << x << " type: " << #y << std::endl;

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
    MidiInputPort* port = static_cast<MidiInputPort*>(  userData );
    if (port != nullptr) {
        port->processMessage( deltatime , message);
    }
}

MidiMessageType MidiInputPort::getMidiMessageType(unsigned char status )
{
    unsigned char type = status & 0xF0;
    return static_cast<MidiMessageType>(  type );
}

int MidiInputPort::getChannel(unsigned char status)
{
    return status & 0x0F;
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
    midiport_.ignoreTypes(  ignoreSysEx ,  ignoreTiming ,  ignoreSensing  );
}

void MidiInputPort::processMessage(
        double deltatime,
        std::vector<unsigned char> *message)
{
    unsigned int nBytes = message->size();
    if (nBytes == 0 ) {
        return;
    }

    unsigned char status_byte = message->at(0);

    std::cout << "status byte = " << (int) status_byte << "\n";
    MidiMessageType message_type = getMidiMessageType( status_byte );
    int channel = getChannel( status_byte  );

    switch (message_type) {
        case MidiMessageType::NoteOn:
            DEBUG( channel ,  MidiMessageType::NoteOn )
            break;

        case MidiMessageType::NoteOff:
            DEBUG( channel , MidiMessageType::NoteOff )
            break;

        case MidiMessageType::ChannelPressure:
            DEBUG( channel, MidiMessageType::ChannelPressure )
            break;

        case MidiMessageType::ControlChange:
            DEBUG( channel , MidiMessageType::ControlChange )
            break;


        case MidiMessageType::PolyphonicKeyPressure:
            DEBUG( channel , MidiMessageType::PolyphonicKeyPressure )
            break;


        case MidiMessageType::ProgramChange:
            DEBUG( channel , MidiMessageType::ProgramChange )
            break;


        case MidiMessageType::PitchBend:
            DEBUG( channel , MidiMessageType::PitchBend )
            break;

        case MidiMessageType::System:
            DEBUG( -1 , MidiMessageType::System )
            break;

        default:
            DEBUG( -1, DEFAULT )
    }



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



