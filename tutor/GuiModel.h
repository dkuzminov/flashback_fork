#pragma once

#include "interface/IGuiModel.h"
#include "interface/ICoach.h"
#include <vector>

QT_BEGIN_NAMESPACE
class QWebView;
QT_END_NAMESPACE

class GuiModel : public IGuiModel, private IGuiModel::ILesson
{
    Q_OBJECT

public:
    static GuiModel& Get();

private:
    class Step : public IStep
    {
        QString GetTask() { return m_coachStep.GetTaskType(); }
        QString GetName() { return m_coachStep.GetName(); }
        void MasterWebControl(QWebView &webView);
    public:
        Step(ICoach::IStep &coachStep, const QString &style)
            : m_coachStep(coachStep),
              m_style(style) {}
    private:
        ICoach::IStep &m_coachStep;
        const QString &m_style;
    };

    GuiModel();
    void Start();
    ILesson& GetLesson() { return *this; }
    void SelectStep(size_t i);

    size_t GetStepCount() { return m_steps.size(); }
    IStep& GetStep(size_t i) { return m_steps[i]; }

    ICoach *m_coach;
    size_t m_selection;
    std::vector<Step> m_steps;
    QString m_style;

private slots:
};

