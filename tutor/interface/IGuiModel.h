#pragma once

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE

namespace guimodel {

class IPageController : public QObject
{
    Q_OBJECT

public:
    virtual void MasterWebControl(QWebView &webView) = 0;
};


class IStep : public QObject
{
    Q_OBJECT

public:
    virtual QString GetTask() = 0;
    virtual QString GetName() = 0;
    virtual IPageController& GetPageController() = 0;

signals:
    void changed();
    void invalidated();
};


class ILesson : public QObject
{
    Q_OBJECT

public:
    virtual size_t GetStepCount() = 0;
    virtual IStep& GetStep(size_t i) = 0;
};


class IGuiModel : public QObject
{
    Q_OBJECT

public:
    virtual void Start() = 0;
    //virtual QString GetUser() = 0;
    //virtual QString GetLanguage() = 0;
    //virtual QString GetStatistic(const QString&) = 0;
    virtual ILesson& GetLesson() = 0;
    virtual void SelectStep(size_t i) = 0;

signals:
    void coachReady();
    void selectionChanged(size_t i, size_t old);
    void statisticsChanged();

public slots:
    //virtual void onGuiReady() = 0;
};

}
