#pragma once

#include "interface/ICoach.h"
#include <memory>

class BaseCoach : public ICoach
{
    size_t GetCount() { return m_stepsPages.size(); }
    ICoach::IStep& GetStep(size_t i) { return *m_stepsPages[i]; }
public:
    virtual ~BaseCoach() {}

protected:
    class StepPage : public ICoach::IStep,
                     private ICoach::IPageContents
    {
        // ICoach::IStep:
        virtual QString GetTaskType() { return m_task; }
        virtual QString GetName() { return m_name; }
        virtual IPageContents& GetPageContents() { return *this; }

        // ICoach::IPageContents:
        const QString& GetTemplate() { return m_template; }

    public:
        StepPage(const QString &task, const QString &name, const QString &templ)
            : m_task(task),
              m_name(name),
              m_template(templ)
        { }

        virtual ~StepPage() {}

    private:
        QString m_task;
        QString m_name;
        QString m_template;
    };

    void x_AddStepPage(std::unique_ptr<StepPage> stepPage)
    {
        m_stepsPages.push_back(std::move(stepPage));
    }

private:
    std::vector<std::unique_ptr<StepPage>> m_stepsPages;
};
