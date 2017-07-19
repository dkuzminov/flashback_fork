QT      +=  core gui sql webkitwidgets

HEADERS =   MainWindow.h \
    interface/ICoach.h \
    interface/IGuiModel.h \
    interface/IRepository.h \
    interface/IGuiPage.h \
    Repositories/SQLite/Database.h \
    Repositories/SQLite/User.h \
    Repositories/MockRepository.h \
    CoachBoard/AlexandraCoach.h \
    CoachBoard/BaseCoach.h \
    CoachBoard/DemoCoach.h \
    CoachBoard/NaiveCoach.h \
    PageControllers/ConfigureUserPageController.h \
    PageControllers/ExercisePageController.h \
    PageControllers/ReadOnlyPageController.h \
    Log.h \
    Settings.h \
    GuiModel.h \
    TabWidget.h \
    GuiPalette.h \
    CoachBoard.h \
    HtmlPageWidget.h
SOURCES =   main.cpp \
    MainWindow.cpp \
    Log.cpp \
    Settings.cpp \
    GuiModel.cpp \
    TabWidget.cpp \
    GuiPalette.cpp \
    CoachBoard.cpp \
    CoachBoard/AlexandraCoach.cpp \
    CoachBoard/DemoCoach.cpp \
    CoachBoard/NaiveCoach.cpp \
    Repositories/SQLite/Database.cpp \
    Repositories/SQLite/User.cpp \
    Repositories/MockRepository.cpp \
    PageControllers/ConfigureUserPageController.cpp \
    PageControllers/ExercisePageController.cpp \
    PageControllers/ReadOnlyPageController.cpp \
    HtmlPageWidget.cpp

FORMS += \
    MainWindow.ui \
    TabWidget.ui \
    GuiPalette.ui \
    HtmlPageWidget.ui

RESOURCES += \
    HtmlTemplates.qrc \
    SqlQueries.qrc

