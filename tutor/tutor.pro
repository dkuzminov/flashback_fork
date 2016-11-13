QT      +=  core gui sql webkitwidgets

HEADERS =   MainWindow.h \
    Log.h \
    Settings.h \
    GuiModel.h \
    interface/IGuiModel.h
SOURCES =   main.cpp \
    MainWindow.cpp \
    Log.cpp \
    Settings.cpp \
    GuiModel.cpp

FORMS += \
    MainWindow.ui

RESOURCES += \
    HtmlTemplates.qrc

