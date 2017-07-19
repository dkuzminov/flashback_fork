#include "CoachBoard/DemoCoach.h"
#include "Log.h"
#include <QFile>
#include <QTextStream>

#if 0
DemoCoach::DemoCoach()
{
    LOG(Note, "Enter DemoCoach::DemoCoach()");
}

void DemoCoach::PrepareLesson()
{
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome", true);
    x_AddStep("Demo", "Textbook", ":/html/templates/demo/mock_repository/TextbookPage1", false);
    x_AddStep("Demo", "Fiction", ":/html/templates/demo/mock_repository/FictionPage1", false);
}

void DemoCoach::x_AddStep(const QString &type, const QString &topic, const QString &resourceName, bool isComplete)
{
    QFile file(resourceName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    m_steps.push_back(Step(type, topic, in.readAll(), isComplete));
}
#endif
