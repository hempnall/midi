#ifndef MIDIINPUTPORT
#define MIDIINPUTPORT

#include <RtMidi.h>
#include <string>
#include "midisystemexclusivemessage.h"
#include "midichannelvoicemessage.h"
#include "midichannelmodemessage.h"


typedef void (*sysexcallbackfunc_t)(const MidiSystemExclusiveMessage& sysex, void* userdata);
typedef void (*voicecallbackfunc_t)(const MidiChannelVoiceMessage& voicemsg, void* userdata);
typedef void (*modemsgcallbackfunc_t)(const MidiChannelModeMessage& modemsg, void* userdata);


enum class MidiMessageType : unsigned char {
    NoteOn = 0x90,
    NoteOff = 0x80,
    PolyphonicKeyPressure = 0xA0,
    ControlChange = 0xB0,
    ProgramChange = 0xC0,
    ChannelPressure = 0xD0,
    PitchBend = 0xE0,
    System = 0xF0
};

template< typename FNPTR , typename T >
void do_callback(  FNPTR fptr , const T& obj , void* userdata)
{

    if (fptr != nullptr) {
        fptr(  obj , userdata );
    }
}

typedef std::vector< unsigned char > mididatabuffer_t;

class MidiInputPort {

    sysexcallbackfunc_t sysexcallback_ ;
    voicecallbackfunc_t voicecallback_ ;
    modemsgcallbackfunc_t modecallback_ ;

    MidiSystemExclusiveMessage sysex_;
    MidiChannelModeMessage modemsg_;
    MidiChannelVoiceMessage voicemsg_;
    void* sysexcallbackobj_ = nullptr;
    void* modemcallbackobj_ = nullptr;
    void* voicecallbackobj_ = nullptr;

    RtMidiIn midiport_;

    MidiMessageType getMidiMessageType( unsigned char status );
    int getChannel(  unsigned char status );

    bool isChannelModeMessage( MidiMessageType type , int byte1 );

    void processChannelVoiceMessage( MidiMessageType type, int channel , int byte1 , int byte2 );
    void processChannelModeMessage(  int channel , int byte1 , int byte2 );
    void processSystemMessage( double deltatime ,  mididatabuffer_t* buffer  );

public:

    void setSysExCallback( sysexcallbackfunc_t fn , void* sysexcallbackobj = nullptr );
    void setModeMsgCallback( modemsgcallbackfunc_t fn , void* modemcallbackobj = nullptr);
    void setVoiceMsgCallback( voicecallbackfunc_t fn  , void* voicecallbackobj = nullptr );

    void listen();
    void processMessage(  double deltatime, mididatabuffer_t *message );

    MidiInputPort();
    MidiInputPort(int n);
    MidiInputPort(  const std::string& name );

    ~MidiInputPort();


    void getInput();




};




#endif // MIDIPORT

