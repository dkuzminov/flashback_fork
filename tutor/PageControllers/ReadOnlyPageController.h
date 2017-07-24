#pragma once
#include "interface/IGuiModel.h"
#include <QObject>
#include <memory>

class ReadOnlyPageController : public guimodel::IPageController
{
    void MasterWebControl(QWebView &webView);

public:
    static std::shared_ptr<ReadOnlyPageController> Get(QString bodyTemplate, QString styleTemplate);

private:
    ReadOnlyPageController(QString bodyTemplate, QString styleTemplate);

    QString m_bodyTemplate;
    QString m_styleTemplate;
};
