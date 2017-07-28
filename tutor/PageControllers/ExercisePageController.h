#pragma once
#include "interface/IGuiModel.h"
#include "interface/ICoach.h"
#include <QObject>
#include <memory>

class ExercisePageController : public guimodel::IPageController
{
    // IGuiModel::IPageController:
    void MasterWebControl(QWebView &webView);

    // TOMController:
    void attachObject();

public:
    static std::unique_ptr<ExercisePageController>
            Get(coach::IPageContents &pageContents, QString styleTemplate);

private:
    ExercisePageController(coach::IPageContents &pageContents, QString styleTemplate)
        : m_pageContents(pageContents),
          m_styleTemplate(styleTemplate)
    {}

    // Ugly hack: I need to store the WebView to attach the TOM when the time comes.
    QWebView *m_webView;
    coach::IPageContents &m_pageContents;
    QString m_styleTemplate;
};
