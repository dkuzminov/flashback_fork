#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWidgets>

#include "HtmlPageWidget.h"

HtmlPageWidget::HtmlPageWidget(IGuiModel::IStep &step, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    step.MasterWebControl(*webView);
}
