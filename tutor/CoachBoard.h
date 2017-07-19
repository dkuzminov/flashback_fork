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
    ICoach* Select(QString couchType,
                   IRepository::IProfile &profile);
    ICoach* SelectDemo();
    inline ICoach& GetCoach();

private:
    CoachBoard();

    std::unique_ptr<BaseCoach> m_coach;
};
