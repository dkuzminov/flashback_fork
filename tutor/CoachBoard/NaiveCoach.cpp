#include "CoachBoard/NaiveCoach.h"
#include "Log.h"
#include <QFile>
#include <QTextStream>

NaiveCoach::NaiveCoach(IRepository::IProfile &profile)
    : m_profile(profile)
{
    LOG(Note, "Enter NaiveCoach::NaiveCoach()");
}

void NaiveCoach::PrepareLesson()
{
    LOG(Note, "Enter NaiveCoach::PrepareLesson()");
    IRepository::IBookmark *textbookBookmark;
    IRepository::IBookmark *fictionBookmark;
    IRepository::IVariable *var = m_profile.GetVariable("TextbookBookmark");
    if (var) {
        textbookBookmark = m_profile.GetBookmark(var->GetValue());
        if (textbookBookmark) {
            x_AddStep("Naive coach", "Textbook", textbookBookmark->GetPage().GetHtml());
        }
        else {
            LOG(Error, "Didn't find bookmark " + var->GetValue());
        }
    }
    else {
        LOG(Note, "Didn't find variable TextbookBookmark");
    }

    var = m_profile.GetVariable("FictionBookmark");
    if (var) {
        fictionBookmark = m_profile.GetBookmark(var->GetValue());
        if (fictionBookmark) {
            x_AddStep("Naive coach", "Fiction", fictionBookmark->GetPage().GetHtml());
        }
        else {
            LOG(Error, "Didn't find bookmark " + var->GetValue());
        }
    }
    else {
        LOG(Note, "Didn't find variable FictionBookmark");
    }
}

void NaiveCoach::x_AddStep(const QString &type, const QString &topic, const QString &html)
{
    m_steps.push_back(Step(type, topic, html));
}
