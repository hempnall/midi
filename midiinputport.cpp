#include "midiinputport.h"
#include <vector>

#define DEBUG( x , y ) std::cout << "[DEBUG] channel: " << x << " type: " << #y << std::endl;

void mycallback( double deltatime, mididatabuffer_t *message, void *userData )
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

bool MidiInputPort::isChannelModeMessage(MidiMessageType midimsgtype, int byte1)
{
    return midimsgtype == MidiMessageType::ControlChange && ( byte1 >= 0x79 && byte1 <= 0x7f) ;
}

void MidiInputPort::processChannelVoiceMessage(MidiMessageType type, int channel, int byte1, int byte2)
{

}

void MidiInputPort::processChannelModeMessage(int channel, int byte1, int byte2)
{

}

void MidiInputPort::processSystemMessage(double deltatime, mididatabuffer_t *buffer)
{
    unsigned int nBytes = buffer->size();
    if (nBytes >= 1) {
        sysex_.readMessage( buffer );
        do_callback( sysexcallback_ , sysex_ , sysexcallbackobj_ );
    }
}

void MidiInputPort::setSysExCallback(sysexcallbackfunc_t fn, void* sysexcallbackobj)
{
    sysexcallback_ = fn;
    sysexcallbackobj_ = sysexcallbackobj;
}

void MidiInputPort::setModeMsgCallback(modemsgcallbackfunc_t fn, void* modemsgcallbackobj)
{
    modecallback_ = fn;
    modemcallbackobj_ = modemsgcallbackobj;
}

void MidiInputPort::setVoiceMsgCallback(voicecallbackfunc_t fn, void* voicemsgcallbackobj)
{
    voicecallback_ = fn;
    voicecallbackobj_ = voicemsgcallbackobj;
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
        mididatabuffer_t *message
        )
{
    unsigned int nBytes = message->size();
    if (nBytes == 0 ) {
        return;
    }

    unsigned char status_byte = message->at(0);
    int byte1 = nBytes >= 2 ? byte1 = message->at(1) : -1;
    int byte2 = nBytes >= 3 ? byte1 = message->at(2) : -1;

    std::cout << "status byte = " << (int) status_byte << "\n";
    MidiMessageType message_type = getMidiMessageType( status_byte );
    int channel = getChannel( status_byte  );

    switch (message_type) {
        case MidiMessageType::NoteOn:
        case MidiMessageType::NoteOff:
        case MidiMessageType::ChannelPressure:
        case MidiMessageType::PolyphonicKeyPressure:
        case MidiMessageType::ProgramChange:
        case MidiMessageType::PitchBend:
            processChannelVoiceMessage( message_type , channel , byte1 , byte2  );
            break;

        case MidiMessageType::ControlChange:
            if ( isChannelModeMessage( message_type , byte1 ) ) {
                processChannelModeMessage( channel , byte1 , byte2 ) ;
            } else {
                processChannelVoiceMessage(message_type , channel , byte1 , byte2 );
            }
            break;

        case MidiMessageType::System:
            processSystemMessage( deltatime,  message );
            break;

        default:
            DEBUG( -1, DEFAULT )
    }

}



MidiInputPort::MidiInputPort()
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



