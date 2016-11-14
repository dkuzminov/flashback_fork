#pragma once

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

struct IGuiModel : public QObject
{
    Q_OBJECT

public:
    struct ILesson
    {
        virtual size_t GetStepCount() = 0;
    };

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
