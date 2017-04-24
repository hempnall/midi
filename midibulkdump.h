#ifndef MIDIBULKDUMP_H
#define MIDIBULKDUMP_H

#include <QDataStream>
#include <QVector>
#include <QByteArray>
#include "midiinputport.h"
#include "midioutputport.h"

typedef QVector<QByteArray> sysex_messages_t;

class MidiBulkDump
{

    friend QDataStream& operator<<(QDataStream& , const MidiBulkDump& );
    friend QDataStream& operator>>(QDataStream& , MidiBulkDump& );

    quint16 count_of_messages_;
    sysex_messages_t sysex_messages_;

public:
    MidiBulkDump();
    ~MidiBulkDump();

    void addSysExMessage( std::vector< unsigned char > const * sysex );
    void sendToMidiPort( MidiOutputPort& port );

};

QDataStream& operator<<(QDataStream& , const MidiBulkDump& );
QDataStream& operator>>(QDataStream& , MidiBulkDump& );


#endif // MIDIBULKDUMP_H
