#pragma once

#include "interface/IGuiModel.h"
#include <memory>
#include <vector>

namespace coach
{
class ICoach;
}

class GuiModel : public guimodel::IGuiModel,
                 private guimodel::ILesson
{
    Q_OBJECT

public:
    static GuiModel& Get();

private:
    class Step : public guimodel::IStep
    {
        QString GetTask() { return m_task; }
        QString GetName() { return m_name; }
        guimodel::IPageController& GetPageController() { return *m_pageController; }

    public:
        Step(QString task, QString name, std::shared_ptr<guimodel::IPageController> controller)
            : m_task(task), m_name(name), m_pageController(controller)
        {}
        void Update(QString task, QString name);
        void Invalidate();
    private:
        QString m_task;
        QString m_name;
        std::shared_ptr<guimodel::IPageController> m_pageController;
    };

    GuiModel();

    // guimodel::IGuiModel
    void Start();
    guimodel::ILesson& GetLesson() { return *this; }
    void SelectStep(size_t i);

    // guimodel::ILesson
    size_t GetStepCount() { return m_steps.size(); }
    guimodel::IStep& GetStep(size_t i) { return *m_steps[i]; }

    coach::ICoach *m_coach;
    size_t m_selection;
    std::vector<std::shared_ptr<Step>> m_steps;
    QString m_style;

private slots:
};

