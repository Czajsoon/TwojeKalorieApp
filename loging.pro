QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createaccount.cpp \
    main.cpp \
    login.cpp \
    reading_users_functions.cpp \
    users_functions.cpp

HEADERS += \
    createaccount.h \
    login.h \
    reading_users_functions.h \
    struct_list_users.h \
    users_functions.h

FORMS += \
    createaccount.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
