#pragma once

#include <QWidget>
#include "interface/ICoach.h"
#include "interface/IRepository.h"
#include <memory>

class BaseCoach;

class CoachBoard
{
public:
    static CoachBoard& Get();
    coach::ICoach* Select(QString couchType,
                          repository::IProfile &profile);
    coach::ICoach* SelectDemo();
    inline coach::ICoach& GetCoach();

private:
    CoachBoard();

    std::unique_ptr<BaseCoach> m_coach;
};
