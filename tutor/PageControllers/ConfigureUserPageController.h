#pragma once
#include "interface/IGuiModel.h"
#include <QObject>
#include <memory>

class ConfigureUserPageController_impl;

class ConfigureUserPageController : public guimodel::IPageController
{
    void MasterWebControl(QWebView &webView);

public:
    static std::shared_ptr<ConfigureUserPageController> Get();

private:
    ConfigureUserPageController();

    std::shared_ptr<ConfigureUserPageController> m_ptr;
    std::shared_ptr<ConfigureUserPageController_impl> m_pImpl;
};

class ConfigureUserPageController_impl : public QObject
{
    Q_OBJECT

public:
    ConfigureUserPageController_impl(QWebView &webView);

protected slots:
    void attachObject();
    void onNameChanged(QString value);
    void onLanguageChanged(QString value);
    void onCoachChanged(QString value);

private:
    QWebView &m_webView;
};
