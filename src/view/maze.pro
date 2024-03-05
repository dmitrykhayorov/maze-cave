QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../back/cavegenerator.cc \
    ../back/mazegenerator.cc \
    ../back/parser.cc \
    ../back/writer.cc \
    ../controller/controller.cc \
    main.cc \
    mainwindow.cc \
    scene.cc

HEADERS += \
    ../back/cavegenerator.h \
    ../back/mazegenerator.h \
    ../back/parser.h \
    ../back/solver.h \
    ../back/writer.h \
    ../controller/controller.h \
    mainwindow.h \
    scene.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
