#include "GuiModel.h"
#include "Database.h"
#include "CoachBoard.h"
#include "Settings.h"
#include "Log.h"
#include <QtWebKit>
#include <QtWebKitWidgets>

GuiModel& GuiModel::Get()
{
    static GuiModel instance;
    return instance;
}

GuiModel::GuiModel()
    : m_selection(-1)
{
    LOG(Note, "Enter GuiModel::GuiModel()");
}

void GuiModel::Start()
{
    // First of all, retrieve the coach type from the database
    Database &database = Database::Get();
    QString databasePath = BasicSettings::Get().GetDatabasePath();
    if (database.Connect(databasePath)) {
        IRepository& repo = database.GetRepository();
        IRepository::IUser* user = repo.GetUser();
        if (user) {
            LOG(Note, "User: " + user->GetName());
            IRepository::IProfile* profile = user->GetProfile();
            if (profile) {
                LOG(Note, "Profile: " + profile->GetProfileName());
                QString coachType = profile->GetCoach();
                LOG(Note, "Coach for this profile: " + coachType);
                CoachBoard &board = CoachBoard::Get();
                board.Select(coachType/*, profile*/);
            }
            else {
                LOG(Note, "No profile exists for this user");
                // ToDo: IDatabase::IProfile* profile = user->CreateProfile();
            }
        }
        else {
            LOG(Note, "No user selected in repository");
            // Do something to manage users
        }

        // retrieve coach
        // for now the coach type is hardcoded
        CoachBoard &board = CoachBoard::Get();
        //board.Select("type", profile);
        m_coach = board.SelectDemo();
    }
    else {
        CoachBoard &board = CoachBoard::Get();
        m_coach = board.SelectDemo();
    }
    m_coach->PrepareLesson();
    for (int i = 0; i < m_coach->GetCount(); ++i) {
        m_steps.push_back(Step(m_coach->GetStep(i)));
    }
}

void GuiModel::SelectStep(size_t i)
{
    if (i != m_selection) {
        emit selectionChanged(i, m_selection);
        m_selection = i;
    }
}

void GuiModel::Step::MasterWebControl(QWebView &webView)
{
    ICoach::IPageInfo &pageInfo = m_coachStep.GetPageInfo();
    webView.setHtml(pageInfo.GetTemplate());
}
