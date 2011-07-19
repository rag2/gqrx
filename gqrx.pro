#-------------------------------------------------
#
# Qmake project file for gqrx
#
#-------------------------------------------------

QT       += core gui

# Ubuntu 10.10 and 11.04: changes due to some strangeness in Debian Qt packages
# Thanks to Andrea IW0HDV
linux-g++ {
    #
    # Try to catch distro informations
    #
    DISTRO=$$system(cat /etc/issue | head -n1 | cut -f1 -d\' \')
    DISTRO_MAJ=$$system(cat /etc/issue | head -n1 | cut -f2 -d\' \' | cut -f1 -d\\.)
    DISTRO_MIN=$$system(cat /etc/issue | head -n1 | cut -f2 -d\' \' | cut -f2 -d\\.)

    # specific to Ubuntu 10.10
    equals(DISTRO,Ubuntu):equals(DISTRO_MAJ,10):equals(DISTRO_MIN,10) {
       message(Linux $$DISTRO $$DISTRO_MAJ $$DISTRO_MIN)
       INCLUDEPATH += $$quote(/usr/include/QtMultimediaKit)
       LIBS += $$quote(-lQtMultimediaKit)
    } else {
       # specific to Ubuntu 11.04
       equals(DISTRO,Ubuntu):equals(DISTRO_MAJ,11):equals(DISTRO_MIN,04) {
          message(Linux $$DISTRO $$DISTRO_MAJ $$DISTRO_MIN)
          INCLUDEPATH += $$quote(/usr/include/QtMobility)
          INCLUDEPATH += $$quote(/usr/include/QtMultimediaKit)
          LIBS += $$quote(-lQtMultimediaKit)
       } else {
          QT += multimedia
       }
    }
} else {
    QT += multimedia
}


TARGET = gqrx
TEMPLATE = app

# disable debug messages in release
CONFIG(debug, debug|release) {
    # Define version string (see below for releases)
    VER = $$system(git describe --abbrev=8)
} else {
    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
    VER = 2.0
}

# Tip from: http://www.qtcentre.org/wiki/index.php?title=Version_numbering_using_QMake
VERSTR = '\\"$${VER}\\"'          # place quotes around the version string
DEFINES += VERSION=\"$${VERSTR}\" # create a VERSION macro containing the version string

SOURCES +=\
    receiver.cc \
    main.cc \
    mainwindow.cc \
    qtgui/freqctrl.cpp \
    qtgui/meter.cpp \
    qtgui/plotter.cpp \
    dsp/rx_fft.cc \
    dsp/rx_filter.cc \
    dsp/rx_demod_fm.cc \
    dsp/rx_meter.cc \
    qtgui/dockinput.cpp \
    qtgui/dockrxopt.cc \
    dsp/rx_demod_am.cc \
    dsp/rx_audio_buffer.cc \
    soundout.cpp \
    dsp/fractresampler.cpp


HEADERS  += mainwindow.h \
    receiver.h \
    qtgui/freqctrl.h \
    qtgui/meter.h \
    qtgui/plotter.h \
    dsp/rx_fft.h \
    dsp/rx_filter.h \
    dsp/rx_demod_fm.h \
    dsp/rx_meter.h \
    qtgui/dockinput.h \
    qtgui/dockrxopt.h \
    dsp/rx_demod_am.h \
    dsp/rx_audio_buffer.h \
    soundout.h \
    dsp/fractresampler.h \
    dsp/datatypes.h

FORMS    += mainwindow.ui \
    qtgui/dockinput.ui \
    qtgui/dockrxopt.ui


# dependencies via pkg-config
# FIXME: check for version?
linux-g++ {
    CONFIG += link_pkgconfig
    PKGCONFIG += gnuradio-core gnuradio-audio gnuradio-fcd
}
