TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

QMAKE_MAC_SDK = macosx10.12
SOURCES += main.cpp \
    midiinputport.cpp \
    midioutputport.cpp \
    midimessage.cpp \
    midichannelmessage.cpp \
    midisystemmessage.cpp \
    midisystemexclusivemessage.cpp \
    midichannelvoicemessage.cpp \
    midichannelmodemessage.cpp \
    midibulkdump.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += /usr/local/include/rtmidi /usr/local/include/

LIBS += -L/usr/local/lib -lrtmidi -lc++ -L/usr/local/lib -lboost_serialization

HEADERS += \
    midi.h \
    midiinputport.h \
    midioutputport.h \
    midimessage.h \
    midichannelmessage.h \
    midisystemmessage.h \
    midisystemexclusivemessage.h \
    midichannelvoicemessage.h \
    midichannelmodemessage.h \
    midibulkdump.h

DISTFILES += \
    README.md

