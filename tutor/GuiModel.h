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
    void SelectStep(size_t i);

    // Temporary hardcoded 3:
    size_t GetCount() { return 3; }

    size_t m_selection;

private slots:
};

