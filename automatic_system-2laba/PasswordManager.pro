QT += core gui quick widgets multimedia multimediawidgets qml network printsupport webview
CONFIG +=  c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        manager.cpp \
        sitemodel.cpp

RESOURCES += qml.qrc


INCLUDEPATH += \
        E:\qtproj\PasswordManager\Win_x64\include\openssl # загаловочные файлы
LIBS += \
        E:\qtproj\PasswordManager\Win_x64\lib\libcrypto.lib # библиотека, содержащая таблицу соответствий названий функций и их адресов
INCLUDEPATH += E:/qtproj/PasswordManager/Win_x64/include
LIBS += -L"E:/qtproj/PasswordManager/Win_x64"

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    manager.h \
    sitemodel.h

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

