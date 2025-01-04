QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# 添加 zlib 库
LIBS += -lz

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backup.cpp \
    extra.cpp \
    filefilter.cpp \
    main.cpp \
    restore.cpp \
    widget.cpp

HEADERS += \
    backup.h \
    extra.h \
    filefilter.h \
    restore.h \
    widget.h

FORMS += \
    backup.ui \
    extra.ui \
    filefilter.ui \
    restore.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img/img.qrc

