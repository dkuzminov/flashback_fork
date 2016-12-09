QT      +=  core gui sql webkitwidgets

HEADERS =   MainWindow.h \
    interface/ICoach.h \
    interface/IGuiModel.h \
    interface/IRepository.h \
    CoachBoard/BaseCoach.h \
    CoachBoard/DemoCoach.h \
    CoachBoard/NaiveCoach.h \
    PageControllers/ConfigureUserPageController.h \
    Log.h \
    Settings.h \
    GuiModel.h \
    TabWidget.h \
    GuiPalette.h \
    CoachBoard.h \
    HtmlPageWidget.h \
    Database.h \
    MockRepository.h
SOURCES =   main.cpp \
    MainWindow.cpp \
    Log.cpp \
    Settings.cpp \
    GuiModel.cpp \
    TabWidget.cpp \
    GuiPalette.cpp \
    CoachBoard.cpp \
    CoachBoard/DemoCoach.cpp \
    CoachBoard/NaiveCoach.cpp \
    PageControllers/ConfigureUserPageController.cpp \
    HtmlPageWidget.cpp \
    Database.cpp \
    MockRepository.cpp

FORMS += \
    MainWindow.ui \
    TabWidget.ui \
    GuiPalette.ui \
    HtmlPageWidget.ui

RESOURCES += \
    HtmlTemplates.qrc \
    SqlQueries.qrc

