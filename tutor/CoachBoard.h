#pragma once

#include <QWidget>
#include "interface/ICoach.h"

class Coach;

class CoachBoard
{
public:
    static CoachBoard& Get();
    ICoach* Select(QString couchType/*, database*/);
    ICoach* SelectDemo();
    inline ICoach& GetCoach();

private:
    CoachBoard();

    Coach *m_coach;
};
