#pragma once

#include <QWidget>
#include "interface/ICoach.h"
#include "interface/IRepository.h"

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

    BaseCoach *m_coach;
};
