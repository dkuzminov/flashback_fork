#pragma once

#include <QObject>

struct ICoach : public QObject
{
    Q_OBJECT

public:
    struct IPageInfo
    {
        virtual const QString& GetTemplate() = 0;
        virtual bool IsComplete() = 0;
        //virtual IFeatures GetFeatures() = 0;
    };

    struct IStep
    {
        virtual QString GetTaskType() = 0;
        virtual QString GetName() = 0;
        virtual IPageInfo& GetPageInfo() = 0;
    };

    virtual void PrepareLesson() = 0;
    virtual size_t GetCount() = 0;
    virtual IStep& GetStep(size_t n) = 0;

signals:

public slots:
};
