#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWidgets>

#include "HtmlPageWidget.h"

HtmlPageWidget::HtmlPageWidget(guimodel::IStep &step, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    step.GetPageController().MasterWebControl(*webView);
    buttonsGroupWidget->setVisible(false);
}
