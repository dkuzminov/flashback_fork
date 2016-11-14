#include "CoachBoard.h"
#include "CoachBoard/DemoCoach.h"
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

ICoach* CoachBoard::Select(QString type/*, database*/)
{
    /*if (type == "demo") {
        m_coach = new DemoCoach();
    }*/
    /*else {
        m_coach = new TestAgent();
    }*/
    return NULL;
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
