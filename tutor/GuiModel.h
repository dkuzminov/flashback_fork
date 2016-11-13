#pragma once

#include "interface/IGuiModel.h"

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE


class GuiModel : public IGuiModel
{
    Q_OBJECT

public:
    static GuiModel& Get();

private:
    GuiModel();
    void Start();

private slots:
};

