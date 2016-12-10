#include "ReadOnlyPageController.h"
#include "Log.h"
#include "Settings.h"
#include <QFile>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>


std::shared_ptr<ReadOnlyPageController> ReadOnlyPageController::Get(QString bodyTemplate, QString styleTemplate)
{
    return std::shared_ptr<ReadOnlyPageController>(new ReadOnlyPageController(bodyTemplate, styleTemplate));
}

ReadOnlyPageController::ReadOnlyPageController(QString bodyTemplate, QString styleTemplate)
    : m_bodyTemplate(bodyTemplate), m_styleTemplate(styleTemplate)
{
}

void ReadOnlyPageController::MasterWebControl(QWebView &webView)
{
    if (m_bodyTemplate.indexOf("<html>", Qt::CaseInsensitive) != -1) {
        LOG(Warning, "The body template has <html> tag");
    }
    QString pageTemplate = "<html><head><style id='general'>%style%</style></head><body>%body%</body></html>";
    if (BasicSettings::Get().NeedApplyStylesImmediately()) {
        pageTemplate.replace("%style%", m_styleTemplate);
    }
    webView.setHtml(pageTemplate.replace("%body%", m_bodyTemplate));
}
