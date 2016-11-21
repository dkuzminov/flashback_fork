#pragma once

#include "CoachBoard/BaseCoach.h"
#include "interface/IRepository.h"
#include <memory>

class NaiveCoach : public BaseCoach
{
public:
    NaiveCoach(IRepository::IProfile &profile);

private:
    struct Step : public IStep {
        Step(const QString &task, const QString &name, const QString &templ)
            : m_task(task), m_name(name), m_pageInfo(new PageInfo(templ)) {}
        virtual QString GetTaskType() { return m_task; }
        virtual QString GetName() { return m_name; }
        virtual IPageInfo& GetPageInfo() { return *m_pageInfo.get(); }

    private:
        QString m_task;
        QString m_name;
        std::shared_ptr<PageInfo> m_pageInfo;
    };

    void PrepareLesson();
    size_t GetCount() { return m_steps.size(); }
    IStep& GetStep(size_t i) { return m_steps[i]; }

    void x_AddStep(const QString &type, const QString &topic, const QString &html);

    IRepository::IProfile &m_profile;
    std::vector<Step> m_steps;
};
