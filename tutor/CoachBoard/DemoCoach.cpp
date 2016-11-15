#include "CoachBoard/DemoCoach.h"
#include <QFile>
#include <QTextStream>
#include "Log.h"

DemoCoach::DemoCoach()
{
    LOG(Note, "Enter DemoCoach::DemoCoach()");
}

void DemoCoach::PrepareLesson()
{
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome");
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome");
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome");
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome");
    x_AddStep("Demo", "Welcome", ":/html/templates/demo/Welcome");
}

void DemoCoach::x_AddStep(const QString &type, const QString &topic, const QString &resourceName)
{
    QFile file(resourceName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    m_steps.push_back(Step(type, topic, in.readAll()));
}
