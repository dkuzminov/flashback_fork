#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWidgets>

#include "HtmlPageWidget.h"

HtmlPageWidget::HtmlPageWidget(guimodel::IStep &step, QWidget *parent)
    : QWidget(parent),
      m_step(step)
{
    setupUi(this);
    step.GetPageController().MasterWebControl(*webView);
    buttonsGroupWidget->setVisible(false);
}

void HtmlPageWidget::Invalidate()
{
    m_step.GetPageController().MasterWebControl(*webView);
}
