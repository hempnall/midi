#ifndef MIDIINPUTPORT
#define MIDIINPUTPORT

#include <RtMidi.h>
#include <string>
#include "midisystemexclusivemessage.h"
#include "midichannelvoicemessage.h"
#include "midichannelmodemessage.h"


typedef void (*sysexcallbackfunc_t)(const MidiSystemExclusiveMessage& sysex);
typedef void (*voicecallbackfunc_t)(const MidiChannelVoiceMessage& voicemsg);
typedef void (*modemsgcallbackfunc_t)(const MidiChannelModeMessage& modemsg);

template< typename FNPTR , typename T >
void do_callback(  FNPTR fptr , const T& obj )
{
    if (fptr != nullptr) {
        fptr(  obj );
    }
}


class MidiInputPort {

    sysexcallbackfunc_t sysexcallback_;
    voicecallbackfunc_t voicecallback_;
    modemsgcallbackfunc_t modecallback_;

    MidiSystemExclusiveMessage sysex_;
    MidiChannelModeMessage modemsg_;
    MidiChannelVoiceMessage voicemsg_;

    RtMidiIn midiport_;

public:

    void setSysExCallback( sysexcallbackfunc_t fn  );
    void setModeMsgCallback( modemsgcallbackfunc_t fn);
    void setVoiceMsgCallback( voicecallbackfunc_t fn  );

    void listen();
    void processMessage(  double deltatime, std::vector< unsigned char > *message );

    MidiInputPort();
    MidiInputPort(int n);
    MidiInputPort(  const std::string& name );

    ~MidiInputPort();


    void getInput();




};




#endif // MIDIPORT

