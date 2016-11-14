#pragma once
#include "ui_GuiPalette.h"

class GuiPalette : public QObject, private Ui_PalettesWidget
{
    Q_OBJECT
public:
    static GuiPalette& Get();
    QPalette GetPalette();

signals:

public slots:
private:
    explicit GuiPalette(QObject *parent = 0);
    QWidget *m_widget;
};

