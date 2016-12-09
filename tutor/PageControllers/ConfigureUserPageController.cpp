#include "ConfigureUserPageController.h"
#include "Log.h"
#include <QFile>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>


std::shared_ptr<ConfigureUserPageController> ConfigureUserPageController::Get()
{
    static ConfigureUserPageController instance;
    return instance.m_ptr;
}

ConfigureUserPageController::ConfigureUserPageController()
    : m_ptr(this, [](ConfigureUserPageController*) {/* empty deleter */})
{
}

void ConfigureUserPageController::MasterWebControl(QWebView &webView)
{
    m_pImpl.reset(new ConfigureUserPageController_impl(webView));
}

ConfigureUserPageController_impl::ConfigureUserPageController_impl(QWebView &webView)
    : m_webView(webView)
{
    QFile file(":/html/templates/service/UserProfileSettings");
    file.open(QFile::ReadOnly | QFile::Text);
    QWebPage* webPage = m_webView.page();
    QWebFrame* webFrame = webPage->mainFrame();
    connect(webFrame, &QWebFrame::javaScriptWindowObjectCleared, this, &ConfigureUserPageController_impl::attachObject);
    webView.setHtml(file.readAll());
}

void ConfigureUserPageController_impl::attachObject()
{
    LOG(Note, "ConfigureUserPageController_impl::attachObject()");
    QWebPage* webPage = m_webView.page();
    QWebFrame* webFrame = webPage->mainFrame();
    webFrame->addToJavaScriptWindowObject(QString("tutor"), this);
}

void ConfigureUserPageController_impl::onNameChanged(QString value)
{
    LOG(Note, "onNameChanged " + value);
    QWebFrame *webFrame = m_webView.page()->mainFrame();
    QWebElement documentElement = webFrame->documentElement();
    QWebElement element = documentElement.findFirst("#name-as-connected");
    element.setInnerXml(value.toHtmlEscaped());
}

void ConfigureUserPageController_impl::onLanguageChanged(QString value)
{
    LOG(Note, "onLanguageChanged " + value);
}

void ConfigureUserPageController_impl::onCoachChanged(QString value)
{
    LOG(Note, "onCoachChanged " + value);
    QWebFrame *webFrame = m_webView.page()->mainFrame();
    QWebElement documentElement = webFrame->documentElement();
    QWebElement element = documentElement.findFirst("#naive-coach-settings");

    if (value.isEmpty()) {
        element.setStyleProperty("display", "none");
    }
    else {
        element.setStyleProperty("display", "block");
    }
}
