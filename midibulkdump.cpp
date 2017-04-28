#include "midibulkdump.h"
#include <QDebug>
#include <unistd.h>
#include <iostream>

MidiBulkDump::MidiBulkDump()
    : count_of_messages_(0)
{

}

MidiBulkDump::~MidiBulkDump()
{

}

void MidiBulkDump::addSysExMessage(std::vector<unsigned char> const *sysex)
{
    count_of_messages_++;
    sysex_messages_.push_back(  *sysex  );

}

void MidiBulkDump::sendToMidiPort(MidiOutputPort &port)
{
    if (  count_of_messages_ != sysex_messages_.size() ) {
        std::cout << "incorrect count of sysex messages";
        return;
    }

    for (auto sysexmsg : sysex_messages_) {
        std::vector<unsigned char> msg( sysexmsg.begin() , sysexmsg.end() );
        port.sendMessage( &msg );
        usleep(10000);
    }
}




//std::ostream& operator<<(std::ostream& strm,  const MidiBulkDump&  dump )
//{
//    template_write( strm, dump.count_of_messages_);

//    for ( auto sysex : dump.sysex_messages_ ) {
//        template_write( strm, sysex.size()    );
//        for (int i=0; i< sysex.size() ;++i) {
//            template_write( strm, sysex.at(i)  );
//        }
//    }
//}

//std::istream& operator>>(std::istream& strm,  MidiBulkDump&  dump )
//{
//    template_read( strm , &dump.count_of_messages_  );

//    for (uint16_t i = 0 ; i < dump.count_of_messages_ ; ++i ) {
//        size_t count ;
//        template_read( strm , &count  );
//        for (uint16_t idx = 0 ; idx < count ; ++idx) {

//        }
//    }
//}



std::ostream &operator<<(std::ostream &str, const MidiBulkDump &dump)
{
    str << dump.count_of_messages_ << "\n";
    for (const mididatabuffer_t& n : dump.sysex_messages_) {
        str << "mididatabuffer\nsize: " << n.size() << "\n";
        for (unsigned char i: n) {
            str << (int) i << "| ";
        }
        str << "\n";
    }
    return str;
}
