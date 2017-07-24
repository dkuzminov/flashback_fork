#pragma once
#include "interface/IGuiModel.h"
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
            Get(QString bodyTemplate, QString styleTemplate, QObject *tomObject);

private:
    ExercisePageController(QString bodyTemplate, QString styleTemplate, QObject *tomObject)
        : m_bodyTemplate(bodyTemplate),
          m_styleTemplate(styleTemplate),
          m_tomObject(tomObject)
    {}

    // Ugly hack: I need to store the WebView to attach the TOM when the time comes.
    QWebView *m_webView;
    QString m_bodyTemplate;
    QString m_styleTemplate;
    QObject *m_tomObject;
};
