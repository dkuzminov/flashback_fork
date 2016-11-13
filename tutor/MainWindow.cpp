#include <QtGui>
#include <QtWidgets>

#include "MainWindow.h"

#include "Log.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LOG(Note, "Enter MainWindow::MainWindow(...)");
    setupUi(this);

    createActions();
    createMenus();
    createToolBars();
}

void MainWindow::createActions()
{
    connectDatabaseAct = new QAction(QIcon(":/images/new.png"), tr("Connect Database..."), this);
    connectDatabaseAct->setStatusTip(tr("Connect to the database"));
    connect(connectDatabaseAct, SIGNAL(triggered()), this, SLOT(connectDatabase()));

    disconnectDatabaseAct = new QAction(QIcon(":/images/new.png"), tr("Disconnect Database"), this);
    disconnectDatabaseAct->setStatusTip(tr("Disconnect from the database"));
    connect(disconnectDatabaseAct, SIGNAL(triggered()), this, SLOT(disconnectDatabase()));

    savePageAct = new QAction(QIcon(":/images/save.png"), tr("Save Page"), this);
    savePageAct->setStatusTip(tr("Save Page"));
    connect(savePageAct, SIGNAL(triggered()), this, SLOT(savePage()));

    saveAllAct = new QAction(QIcon(":/images/save.png"), tr("Save All"), this);
    saveAllAct->setStatusTip(tr("Save All"));
    connect(saveAllAct, SIGNAL(triggered()), this, SLOT(saveAll()));

    addPageAct = new QAction(QIcon(":/images/new.png"), tr("&Add Page"), this);
    addPageAct->setShortcuts(QKeySequence::New);
    addPageAct->setStatusTip(tr("Add new page"));
    connect(addPageAct, SIGNAL(triggered()), this, SLOT(addPage()));

    removePageAct = new QAction(QIcon(":/images/new.png"), tr("&Remove Page"), this);
    removePageAct->setShortcuts(QKeySequence::Close);
    removePageAct->setStatusTip(tr("Remove page"));
    connect(removePageAct, SIGNAL(triggered()), this, SLOT(removePage()));

    applyStylesAct = new QAction(QIcon(":/images/new.png"), tr("A&pply Styles"), this);
    applyStylesAct->setShortcuts(QKeySequence::New);
    applyStylesAct->setStatusTip(tr("Apply styles"));
    connect(applyStylesAct, SIGNAL(triggered()), this, SLOT(applyStyles()));

    removeSpotAct = new QAction(QIcon(":/images/delete.png"), tr("&Remove Spot"), this);
    removeSpotAct->setShortcuts(QKeySequence::Delete);
    removeSpotAct->setStatusTip(tr("Remove page"));
    connect(removeSpotAct, SIGNAL(triggered()), this, SLOT(removeSpot()));

    highlightSpotsAct = new QAction(QIcon(":/images/save.png"), tr("&Highlight Spots"), this);
    highlightSpotsAct->setStatusTip(tr("Highlight Spots"));
    connect(highlightSpotsAct, SIGNAL(triggered()), this, SLOT(highlightSpots()));

    acceptSpotsAct = new QAction(QIcon(":/images/save.png"), tr("&Accept Spots"), this);
    acceptSpotsAct->setStatusTip(tr("Accept Spots"));
    connect(acceptSpotsAct, SIGNAL(triggered()), this, SLOT(acceptSpots()));


    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    bool showMenu = true;//Settings::Get().ShowMenu();
    if (showMenu) {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(connectDatabaseAct);
        fileMenu->addAction(disconnectDatabaseAct);
        fileMenu->addSeparator();
        fileMenu->addAction(savePageAct);
        fileMenu->addAction(saveAllAct);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAct);

        viewMenu = menuBar()->addMenu(tr("&View"));
        viewMenu->addAction(applyStylesAct);

        menuBar()->addSeparator();

        helpMenu = menuBar()->addMenu(tr("&Help"));
    }
}

void MainWindow::createToolBars()
{
    bool showToolbar = true;//Settings::Get().ShowToolbar();
    if (showToolbar) {
        fileToolBar = addToolBar(tr("File"));
        fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        fileToolBar->addAction(connectDatabaseAct);

        viewToolBar = addToolBar(tr("View"));
        viewToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        viewToolBar->addAction(applyStylesAct);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (1/*maybeSave()*/) {
        //writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_okButton_clicked()
{
    close();
}

void MainWindow::on_postponeButton_clicked()
{
    close();
}

void MainWindow::on_cancelButton_clicked()
{
    close();
}
