#include "CoachBoard.h"
#include "CoachBoard/BaseCoach.h"
#include "CoachBoard/DemoCoach.h"
#include "CoachBoard/NaiveCoach.h"
#include "CoachBoard/AlexandraCoach.h"
#include "Log.h"


CoachBoard& CoachBoard::Get()
{
    static CoachBoard instance;
    return instance;
}

CoachBoard::CoachBoard()
{
}

ICoach* CoachBoard::Select(QString type,
                           IRepository::IProfile &profile)
{
    // Temporary remove any other coaches
    /*if (type == "Naive") {
        m_coach = new NaiveCoach(profile);
    }
    if (type == "Alexandra") {
        m_coach = new AlexandraCoach(profile);
    }
    return m_coach;*/
    return new AlexandraCoach(profile);
}

ICoach* CoachBoard::SelectDemo()
{
    // Temporary remove any other coaches
    /*m_coach = new DemoCoach();*/
    return m_coach.get();
}

ICoach& CoachBoard::GetCoach()
{
    return *m_coach.get();
}
