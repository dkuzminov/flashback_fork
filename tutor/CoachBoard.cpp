#include "CoachBoard.h"
#include "CoachBoard/BaseCoach.h"
#include "CoachBoard/DemoCoach.h"
#include "CoachBoard/NaiveCoach.h"
#include "Log.h"


CoachBoard& CoachBoard::Get()
{
    static CoachBoard instance;
    return instance;
}

CoachBoard::CoachBoard()
    : m_coach(NULL)
{
}

ICoach* CoachBoard::Select(QString type,
                           IRepository::IProfile &profile)
{
    if (type == "Naive") {
        m_coach = new NaiveCoach(profile);
    }
    return m_coach;
}

ICoach* CoachBoard::SelectDemo()
{
    m_coach = new DemoCoach();
    return m_coach;
}

ICoach& CoachBoard::GetCoach()
{
    return *m_coach;
}
