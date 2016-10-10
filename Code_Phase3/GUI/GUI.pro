#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T00:21:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

QMAKE_CXX = g++-5
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
    signupdialog.cpp \
    gui.cpp \
    mainmenu.cpp \
    client.cpp \
    deck.cpp \
    collection.cpp \
    Server\server.cpp \
    Server\carddatabase.cpp \
    card.cpp \
    Server\chatmanager.cpp \
    Server\database.cpp \
    Server\clientsocket.cpp \
    Server\game.cpp \
    Server\gamedeck.cpp \
    Server\matchmaking.cpp \
    Server\player.cpp \
    Server\ranking.cpp \
    Server\user.cpp \
    Server\usermanager.cpp \
    signindialog.cpp \
    graphicalcard.cpp \
    collectiongui.cpp \
    chosedeckdialog.cpp \
    waitingopponentdialog.cpp \
    rankingview.cpp \
    collectionmenudialog.cpp \
    onecarddialog.cpp \
    viewdecksdialog.cpp \
    duelwindow.cpp \
    friendslist.cpp \
    playonecarddialog.cpp \
    canatkdialog.cpp \
    targetsdialog.cpp \
    deletedeckdialog.cpp \
    createdeckdialog.cpp \
    decktomodify.cpp \
    viewonedeck.cpp \
    addcardsondeck.cpp

HEADERS  += \
    signupdialog.h \
    gui.h \
    mainmenu.h \
    client.h \
    deck.h \
    collection.h \
    Server\server.h \
    Server\carddatabase.h \
    card.h \
    Server\chatmanager.h \
    Server\database.h \
    Server\clientsocket.h \
    Server\game.h \
    Server\gamedeck.h \
    Server\matchmaking.h \
    Server\player.h \
    Server\ranking.h \
    Server\user.h \
    Server\usermanager.h \
    signindialog.h \
    graphicalcard.h \
    collectiongui.h \
    chosedeckdialog.h \
    waitingopponentdialog.h \
    rankingview.h \
    collectionmenudialog.h \
    onecarddialog.h \
    viewdecksdialog.h \
    duelwindow.h \
    friendslist.h \
    playonecarddialog.h \
    canatkdialog.h \
    targetsdialog.h \
    deletedeckdialog.h \
    createdeckdialog.h \
    decktomodify.h \
    viewonedeck.h \
    addcardsondeck.h

FORMS    += gui.ui \
    signupdialog.ui \
    mainmenu.ui \
    signindialog.ui \
    graphicalcard.ui \
    collectiongui.ui \
    chosedeckdialog.ui \
    waitingopponentdialog.ui \
    rankingview.ui \
    collectionmenudialog.ui \
    onecarddialog.ui \
    viewdecksdialog.ui \
    duelwindow.ui \
    friendslist.ui \
    playonecarddialog.ui \
    canatkdialog.ui \
    targetsdialog.ui \
    graphicalplayer.ui \
    deletedeckdialog.ui \
    createdeckdialog.ui \
    decktomodify.ui \
    viewonedeck.ui \
    addcardsondeck.ui

RESOURCES += \
    resources.qrc
