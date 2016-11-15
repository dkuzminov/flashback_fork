#pragma once

#include <QObject>

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE

struct IPageMaster
{
    virtual void MasterWebControl(QWebView &webView) = 0;
};

struct ICoach : public QObject
{
    Q_OBJECT

public:
    struct IStep
    {
        virtual QString GetTaskType() = 0;
        virtual QString GetName() = 0;
        virtual IPageMaster& GetPageMaster() = 0;
    };

    virtual void PrepareLesson() = 0;
    virtual size_t GetCount() = 0;
    virtual IStep& GetStep(size_t n) = 0;

signals:

public slots:
};
