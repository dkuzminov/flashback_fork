#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
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
};
