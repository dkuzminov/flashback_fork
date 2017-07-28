#include "ExercisePageController.h"
#include "Log.h"
#include "Settings.h"
#include <QFile>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>


std::unique_ptr<ExercisePageController>
        ExercisePageController::Get(coach::IPageContents &pageContents, QString styleTemplate)
{
    return std::unique_ptr<ExercisePageController>(
                new ExercisePageController(pageContents, styleTemplate));
}

void ExercisePageController::MasterWebControl(QWebView &webView)
{
    m_webView = &webView;
    QWebPage* webPage = webView.page();
    QWebFrame* webFrame = webPage->mainFrame();
    connect(webFrame, &QWebFrame::javaScriptWindowObjectCleared, this, &ExercisePageController::attachObject);

    QString pageTemplate =
            "<html><head><style id='general'>%style%</style></head><body>%body%</body></html>";
    if (BasicSettings::Get().NeedApplyStylesImmediately()) {
        pageTemplate.replace("%style%", m_styleTemplate);
    }
    webView.setHtml(pageTemplate.replace("%body%", m_pageContents.GetTemplate()));
}

void ExercisePageController::attachObject()
{
    QWebPage* webPage = m_webView->page();
    QWebFrame* webFrame = webPage->mainFrame();
    QObject *tomObject = m_pageContents.GetTOMObject();
    if (tomObject) {
        webFrame->addToJavaScriptWindowObject(QString("tutor"), tomObject);
    }
}
