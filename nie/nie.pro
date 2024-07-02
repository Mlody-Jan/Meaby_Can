QT -= gui
CONFIG += c++17 console
CONFIG -= app_bundle

# Disable all APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp

HEADERS += \
    PCANBasic.h

# Dodaj ścieżki do katalogów zawierających pliki nagłówkowe i biblioteki
INCLUDEPATH += "C:/Users/jan.wasilewski/Downloads/PCAN-Basic (1)/include"
LIBS += -L"C:/Users/jan.wasilewski/Downloads/PCAN-Basic (1)/x64/VC_LIB" -lPCANBasic

# Zasady dla różnych platform
unix {
    target.path = /opt/$${TARGET}/bin
    isEmpty(target.path): INSTALLS += target
}

win32 {
    target.path = C:/Users/jan.wasilewski/Documents/nie
    isEmpty(target.path): INSTALLS += target
}
