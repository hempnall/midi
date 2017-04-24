#include "midibulkdump.h"
#include <QDebug>
#include <unistd.h>

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
    QByteArray arr( reinterpret_cast<const char*>( sysex->data() ) , sysex->size() );
    sysex_messages_ << arr;

}

void MidiBulkDump::sendToMidiPort(MidiOutputPort &port)
{
    if (  count_of_messages_ != sysex_messages_.size() ) {
        qDebug() << "incorrect count of sysex messages";
        return;
    }

    for (auto sysexmsg : sysex_messages_) {
        std::vector<unsigned char> msg( sysexmsg.begin() , sysexmsg.end() );
        port.sendMessage( &msg );
        usleep(10000);
    }
}



QDataStream &operator<<(QDataStream &strm, const MidiBulkDump &dump)
{
    strm << dump.count_of_messages_ << dump.sysex_messages_;
}


QDataStream &operator>>(QDataStream &strm, MidiBulkDump &dump)
{
    strm >> dump.count_of_messages_ >> dump.sysex_messages_;
}
