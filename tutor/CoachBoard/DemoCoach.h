#pragma once

#include "interface/ICoach.h"
#include <memory>

class Coach : public ICoach
{
public:
    virtual ~Coach() {}
};

class BasePageMaster : public IPageMaster
{
public:
    virtual ~BasePageMaster() {}
};

class DemoCoach : public Coach
{
public:
    DemoCoach();

private:
    struct Step : public IStep {
        Step(QString task, QString name, BasePageMaster *pageMaster)
            : m_task(task), m_name(name), m_pageMaster(pageMaster) {}
        virtual QString GetTaskType() { return m_task; }
        virtual QString GetName() { return m_name; }
        virtual IPageMaster& GetPageMaster() { return *m_pageMaster.get(); }
    private:
        QString m_task;
        QString m_name;
        std::shared_ptr<BasePageMaster> m_pageMaster;
    };

    void PrepareLesson();
    size_t GetCount() { return m_steps.size(); }
    IStep& GetStep(size_t i) { return m_steps[i]; }

    void x_AddStep(const QString &type, const QString &topic, BasePageMaster *pageMaster);

    std::vector<Step> m_steps;
};
