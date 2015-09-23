######################################################################
# Automatically generated by qmake (2.01a) Sun Jul 5 17:49:45 2015
######################################################################

TEMPLATE = app
TARGET =
DEPENDPATH += . 2
INCLUDEPATH += . 2

QT += core gui

# Input
HEADERS += MainWindow.h \
           generated/ui_samplebrain.h \

SOURCES += MainWindow.cpp \
           audio_thread.cpp \
           process_thread.cpp \
           feedback.cpp \
           qtmain.cpp \
           ../src/block.cpp \
           ../src/brain.cpp \
           ../src/fft.cpp \
           ../src/mfcc.cpp \
           ../src/renderer.cpp \
           ../src/status.cpp \
           ../src/window.cpp \
           ../src/pitchshift.cpp \
           ../src/aquila/filter/MelFilterBank.cpp \
           ../src/aquila/filter/MelFilter.cpp \
           ../src/aquila/transform/Dct.cpp \
           ../../../jellyfish/src/fluxa/sample.cpp \
           ../../../jellyfish/src/fluxa/ring_buffer.cpp \
           ../../../jellyfish/src/fluxa/command_ring_buffer.cpp \
           ../../../jellyfish/src/audio/portaudio_client.cpp \
           ../../../jellyfish/src/audio.cpp \
           ../../../jellyfish/src/fluxa/OSC_server.cpp \
           ../../../jellyfish/src/fluxa/allocator.cpp \
           ../../../jellyfish/src/core/stream.cpp

INCLUDEPATH += ../src
LIBS += -L.. -lrubberband -lportaudio -lfftw3 -lsndfile -llo -ldl -lpthread -lm
#CONFIG+=debug

QMAKE_CXXFLAGS += -Wall -Wno-unused -std=c++11 -DDONT_USE_FLUXA_GRAPH

# assets
RESOURCES     = samplebrain.qrc
