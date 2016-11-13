#pragma once

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

struct IGuiModel : public QObject
{
    Q_OBJECT

public:
    virtual void Start() = 0;
    //virtual QString GetUser() = 0;
    //virtual QString GetLanguage() = 0;
    //virtual QString GetStatistic(const QString&) = 0;

signals:
    void coachReady();
    void selectionChanged(size_t old, size_t _new);
    void statisticsChanged();

public slots:
    //virtual void onGuiReady() = 0;
};
