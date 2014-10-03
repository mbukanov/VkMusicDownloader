QT += gui widgets

LIBS += -L"$$_PRO_FILE_PWD_" -lcurl -lboost_regex -ljsoncpp -lm -lcrypto

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    window.cpp \
    authwidget.cpp \
    vkapi.cpp \
    FileDownloader.cpp \
    musiclist.cpp \
    fileoperations.cpp \
    settingswidget.cpp

HEADERS += \
    window.h \
    authwidget.h \
    vkapi.h \
    FileDownloader.h \
    musiclist.h \
    fileoperations.h \
    OS.h \
    settingswidget.h
