#pragma once

#include <QObject>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

struct ICoach : public QObject
{
    Q_OBJECT

public:
    struct IStep
    {
        virtual QString GetTaskType() = 0;
        virtual QString GetName() = 0;
    };

    virtual void PrepareLesson() = 0;
    virtual size_t Count() = 0;
    virtual IStep& GetStep(size_t n) = 0;

signals:

public slots:
};
