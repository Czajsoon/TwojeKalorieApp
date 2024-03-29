QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addingnewmeal.cpp \
    createaccount.cpp \
    deletecategorywin.cpp \
    deleteproductwin.cpp \
    funkcje.cpp \
    funkcjeProduktow.cpp \
    globals.cpp \
    kalkulator.cpp \
    main.cpp \
    login.cpp \
    mealFunctions.cpp \
    mealReadWriteFunctions.cpp \
    mojdzienik.cpp \
    newcategorywin.cpp \
    newproductwin.cpp \
    readingCategoriesAndProducts.cpp \
    reading_users_functions.cpp \
    sharedmeals.cpp \
    users_functions.cpp \
    writingFunctionsCategorieAndProducts.cpp \
    writing_functions.cpp

HEADERS += \
    addingnewmeal.h \
    createaccount.h \
    deletecategorywin.h \
    deleteproductwin.h \
    funkceProduktow.h \
    funkcje.h \
    globals.h \
    kalkulator.h \
    login.h \
    mealFunctions.h \
    mealReadWriteFunctions.h \
    mealStructure.h \
    mojdzienik.h \
    newcategorywin.h \
    newproductwin.h \
    produktyStruktury.h \
    readingCategoriesAndProducts.h \
    reading_users_functions.h \
    sharedmeals.h \
    struct_list_users.h \
    users_functions.h \
    writingFunctionsCategoriesAndProducts.h \
    writing_functions.h

FORMS += \
    addingnewmeal.ui \
    createaccount.ui \
    deletecategorywin.ui \
    deleteproductwin.ui \
    kalkulator.ui \
    login.ui \
    mojdzienik.ui \
    newcategorywin.ui \
    newproductwin.ui \
    sharedmeals.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
