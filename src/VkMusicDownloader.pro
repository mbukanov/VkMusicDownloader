QT += gui widgets

LIBS += -L"$$_PRO_FILE_PWD_" -lcurl -lboost_regex -ljsoncpp -lm -lcrypto

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    window.cpp \
    authwidget.cpp \
    FileDownloader.cpp \
    musiclist.cpp \
    settingswidget.cpp \
    vkmusic.cpp \
    vkbase.cpp \
    settings.cpp \
    musicdownloader.cpp

HEADERS += \
    window.h \
    authwidget.h \
    FileDownloader.h \
    musiclist.h \
    fileoperations.h \
    OS.h \
    settingswidget.h \
    vkmusic.h \
    vkbase.h \
    settings.h \
    musicdownloader.h
