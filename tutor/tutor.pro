QT      +=  core gui sql webkitwidgets

HEADERS =   MainWindow.h \
    Log.h \
    Settings.h \
    GuiModel.h \
    interface/IGuiModel.h \
    TabWidget.h \
    GuiPalette.h \
    interface/ICoach.h \
    CoachBoard.h \
    CoachBoard/DemoCoach.h \
    HtmlPageWidget.h
SOURCES =   main.cpp \
    MainWindow.cpp \
    Log.cpp \
    Settings.cpp \
    GuiModel.cpp \
    TabWidget.cpp \
    GuiPalette.cpp \
    CoachBoard.cpp \
    CoachBoard/DemoCoach.cpp \
    HtmlPageWidget.cpp

FORMS += \
    MainWindow.ui \
    TabWidget.ui \
    GuiPalette.ui \
    HtmlPageWidget.ui

RESOURCES += \
    HtmlTemplates.qrc

