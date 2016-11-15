#pragma once

#include "interface/ICoach.h"
#include <memory>

class Coach : public ICoach
{
public:
    virtual ~Coach() {}
};

class PageInfo : public ICoach::IPageInfo
{
public:
    PageInfo(const QString &templ) : m_template(templ) { }
private:
    const QString& GetTemplate() { return m_template; }

    QString m_template;
};

class DemoCoach : public Coach
{
public:
    DemoCoach();

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

    void x_AddStep(const QString &type, const QString &topic, const QString &resourceName);

    std::vector<Step> m_steps;
};
