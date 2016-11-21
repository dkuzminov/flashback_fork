#pragma once

#include "interface/ICoach.h"

class BaseCoach : public ICoach
{
public:
    virtual ~BaseCoach() {}
};

class PageInfo : public ICoach::IPageInfo
{
public:
    PageInfo(const QString &templ, bool isComplete)
        : m_template(templ),
          m_isComplete(isComplete) { }
private:
    const QString& GetTemplate() { return m_template; }
    bool IsComplete() { return m_isComplete; }

    QString m_template;
    bool m_isComplete;
};
