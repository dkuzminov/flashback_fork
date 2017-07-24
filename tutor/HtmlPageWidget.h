#pragma once

#include <QWidget>
#include "GuiModel.h"
#include "ui_HtmlPageWidget.h"

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE

class HtmlPageWidget : public QWidget,  public Ui_HtmlPageWidget
{
    Q_OBJECT
public:
    HtmlPageWidget(guimodel::IStep &step, QWidget *parent);

private slots:

signals:

private:
    QWebView *pageView;
};
