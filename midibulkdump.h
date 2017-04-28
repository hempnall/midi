#ifndef MIDIBULKDUMP_H
#define MIDIBULKDUMP_H

#include <QDataStream>
#include <QVector>
#include <QByteArray>
#include <iostream>
#include "midiinputport.h"
#include "midioutputport.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

typedef std::vector< mididatabuffer_t > sysex_messages_t;



class MidiBulkDump
{
    friend class boost::serialization::access;
    friend std::ostream& operator<<(std::ostream& str, const MidiBulkDump& dump);

    uint16_t count_of_messages_;
    sysex_messages_t sysex_messages_;

    template< typename Archive >
    void serialize( Archive & ar , const unsigned int version )
    {
        ar & count_of_messages_;
        ar & sysex_messages_;
    }

public:
    MidiBulkDump();
    ~MidiBulkDump();

    void addSysExMessage( mididatabuffer_t const * sysex );
    void sendToMidiPort( MidiOutputPort& port );

};

std::ostream& operator<<(std::ostream& str, const MidiBulkDump& dump);


#endif // MIDIBULKDUMP_H
