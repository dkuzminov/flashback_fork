#pragma once

#include "interface/IGuiModel.h"

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE

class ICoach;

class GuiModel : public IGuiModel, private IGuiModel::ILesson
{
    Q_OBJECT

public:
    static GuiModel& Get();

private:
    GuiModel();
    void Start();
    ILesson& GetLesson() { return *this; }
    void SelectStep(size_t i);

    // Temporary hardcoded 3:
    size_t GetStepCount() { return 3; }

    ICoach *m_coach;
    size_t m_selection;

private slots:
};

