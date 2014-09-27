QT += gui widgets

LIBS += -L"$$_PRO_FILE_PWD_" -lcurl -lboost_regex -ljsoncpp

SOURCES += \
    main.cpp \
    window.cpp \
    authwidget.cpp \
    vkapi.cpp \
    FileDownloader.cpp \
    musiclist.cpp

HEADERS += \
    window.h \
    authwidget.h \
    vkapi.h \
    FileDownloader.h \
    musiclist.h
