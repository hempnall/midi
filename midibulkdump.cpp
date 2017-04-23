#include "midibulkdump.h"

MidiBulkDump::MidiBulkDump()
    : count_of_messages_(0)
{

}

MidiBulkDump::~MidiBulkDump()
{

}

void MidiBulkDump::addSysExMessage(std::vector<unsigned char> *sysex)
{
    count_of_messages_++;
    QByteArray arr( reinterpret_cast<const char*>( sysex->data() ) , sysex->size() );
    sysex_messages_ << arr;

}

void MidiBulkDump::sendToMidiPort(MidiInputPort &port)
{

}



QDataStream &operator<<(QDataStream &strm, const MidiBulkDump &dump)
{
    strm <<
}


QDataStream &operator>>(QDataStream &strm, MidiBulkDump &dump)
{

}
