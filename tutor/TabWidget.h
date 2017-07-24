#pragma once

#include <QWidget>
#include "ui_TabWidget.h"

class TabWidget : public QWidget,  public Ui_TabWidget
{
    Q_OBJECT
public:
    TabWidget(const QString &id, const QString &task, const QString &description, bool isLight, QWidget *parent);
    void setHighlighted(bool enabled);
    void Update(const QString &task, const QString &description);

private slots:
    void selectedChanged(int);

signals:
    void spotSelected(const QString &id, bool state);
    void clicked();

private:
    QString m_id;
    QString m_task;
    QString m_description;
    QBrush m_brush;

    bool event(QEvent *event);
};
