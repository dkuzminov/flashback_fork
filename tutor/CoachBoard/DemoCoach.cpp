#include "CoachBoard/DemoCoach.h"
#include "Log.h"

DemoCoach::DemoCoach()
{
    LOG(Note, "Enter DemoCoach::DemoCoach()");
}

class SimplePageMaster : public BasePageMaster
{
    void MasterWebControl(QWebView &webView) {}
public:
    SimplePageMaster(const QString &filename)
    {
    }
};

void DemoCoach::PrepareLesson()
{
    x_AddStep("Demo", "Welcome", new SimplePageMaster(":/html/templates/demo/Welcome"));
    x_AddStep("Demo", "Welcome", new SimplePageMaster(":/html/templates/demo/Welcome"));
    x_AddStep("Demo", "Welcome", new SimplePageMaster(":/html/templates/demo/Welcome"));
    x_AddStep("Demo", "Welcome", new SimplePageMaster(":/html/templates/demo/Welcome"));
    x_AddStep("Demo", "Welcome", new SimplePageMaster(":/html/templates/demo/Welcome"));
}

void DemoCoach::x_AddStep(const QString &type, const QString &topic, BasePageMaster *pageMaster)
{
    m_steps.push_back(Step(type, topic, pageMaster));
}
