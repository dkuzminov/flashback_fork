#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace guimodel {
struct IGuiModel;
}
class TabWidget;
class HtmlPageWidget;

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(guimodel::IGuiModel& model, QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_lessonReady();
    void on_stepChanged(size_t i);
    void on_tabClicked(size_t i);
    void on_selectionChanged(size_t i, size_t old);
    void on_okButton_clicked();
    void on_postponeButton_clicked();
    void on_cancelButton_clicked();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    //void createStatusBar();

    QAction *connectDatabaseAct;
    QAction *disconnectDatabaseAct;
    QAction *savePageAct;
    QAction *saveAllAct;
    QAction *addPageAct;
    QAction *removePageAct;
    QAction *exitAct;
    QAction *removeSpotAct;
    QAction *highlightSpotsAct;
    QAction *acceptSpotsAct;

    QAction *applyStylesAct;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *viewToolBar;

    guimodel::IGuiModel &m_guiModel;
    std::vector<std::pair<TabWidget*, HtmlPageWidget*>> m_stepWidgets;
};
