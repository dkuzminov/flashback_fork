#pragma once

#include "interface/IGuiModel.h"
#include "interface/ICoach.h"
#include <memory>
#include <vector>

class GuiModel : public IGuiModel, private IGuiModel::ILesson
{
    Q_OBJECT

public:
    static GuiModel& Get();

private:
    class Step : public IStep
    {
        QString GetTask() { return m_task; }
        QString GetName() { return m_name; }
        IPageController& GetPageController() { return *m_pageController; }
    public:
        Step(QString task, QString name, std::shared_ptr<IPageController> controller)
            : m_task(task), m_name(name), m_pageController(controller) {}
    private:
        const QString m_task;
        const QString m_name;
        std::shared_ptr<IPageController> m_pageController;
    };

    GuiModel();
    void Start();
    ILesson& GetLesson() { return *this; }
    void SelectStep(size_t i);

    size_t GetStepCount() { return m_steps.size(); }
    IStep& GetStep(size_t i) { return *m_steps[i]; }

    ICoach *m_coach;
    size_t m_selection;
    std::vector<std::shared_ptr<Step>> m_steps;
    QString m_style;

private slots:
};

