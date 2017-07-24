#pragma once

#include <QObject>

namespace coach {

class IPageContents : public QObject
{
    Q_OBJECT

public:
    virtual const QString& GetTemplate() = 0;
    virtual QObject* GetTOMObject() = 0;
};


class IStep : public QObject
{
    Q_OBJECT

public:
    virtual QString GetTaskType() = 0;
    virtual QString GetName() = 0;
    virtual IPageContents& GetPageContents() = 0;

signals:
    void stepChanged();
};


class ICoach : public QObject
{
    Q_OBJECT

public:
    virtual void PrepareLesson() = 0;
    virtual size_t GetCount() = 0;
    virtual IStep& GetStep(size_t n) = 0;
};

}
