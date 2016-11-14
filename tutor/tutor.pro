QT      +=  core gui sql webkitwidgets

HEADERS =   MainWindow.h \
    Log.h \
    Settings.h \
    GuiModel.h \
    interface/IGuiModel.h \
    CoachBoard/DemoCoach.h \
    TabWidget.h \
    GuiPalette.h
SOURCES =   main.cpp \
    MainWindow.cpp \
    Log.cpp \
    Settings.cpp \
    GuiModel.cpp \
    CoachBoard/DemoCoach.cpp \
    TabWidget.cpp \
    GuiPalette.cpp

FORMS += \
    MainWindow.ui \
    TabWidget.ui \
    GuiPalette.ui

RESOURCES += \
    HtmlTemplates.qrc

