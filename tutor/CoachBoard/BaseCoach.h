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
    PageInfo(const QString &templ) : m_template(templ) { }
private:
    const QString& GetTemplate() { return m_template; }

    QString m_template;
};
