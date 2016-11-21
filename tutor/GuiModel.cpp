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
    QFile file(":/css/general");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    m_style = in.readAll();
}

void GuiModel::Start()
{
    if (!BasicSettings::Get().IsDemoMode()) {
        Database &database = Database::Get();
        QString databasePath = BasicSettings::Get().GetDatabasePath();
        if (database.Connect(databasePath)) {
            IRepository& repo = database.GetRepository();
            IRepository::IUser* user = repo.GetUser();
            if (user) {
                LOG(Note, "GuiModel got user from repository: " + user->GetName());
                IRepository::IProfile& profile = user->GetProfile();
                QString coachType = profile.GetCoachType();
                LOG(Note, "User profile requires a coach: " + coachType);
                CoachBoard &board = CoachBoard::Get();
                m_coach = board.Select(coachType, profile);
            }
            else {
                LOG(Note, "No current user selected in repository");
                // Do something to manage users
            }
        }
    }

    // If nothing else works, use stub:
    if (m_coach == NULL) {
        CoachBoard &board = CoachBoard::Get();
        m_coach = board.SelectDemo();
    }

    m_coach->PrepareLesson();
    for (int i = 0; i < m_coach->GetCount(); ++i) {
        m_steps.push_back(Step(m_coach->GetStep(i), m_style));
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
    QString bodyTemplate = pageInfo.GetTemplate();
    if (bodyTemplate.indexOf("<html>", Qt::CaseInsensitive) != -1) {
        LOG(Warning, "The body template has <html> tag");
    }
    QString pageTemplate = "<html><head><style id='general'>%style%</style></head><body>%body%</body></html>";
    if (BasicSettings::Get().NeedApplyStylesImmediately()) {
        pageTemplate.replace("%style%", m_style);
    }
    webView.setHtml(pageTemplate.replace("%body%", pageInfo.GetTemplate()));
}
