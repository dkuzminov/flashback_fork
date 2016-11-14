#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWidgets>

#include "HtmlPageWidget.h"

HtmlPageWidget::HtmlPageWidget(/*const QString &id, *//*IGuiModel::IStep &step, */QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    webView->setHtml("<html><head></head><body>Stub</body></html>");
}
