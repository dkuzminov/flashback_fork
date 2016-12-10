#include "GuiModel.h"
#include "PageControllers/ConfigureUserPageController.h"
#include "PageControllers/ReadOnlyPageController.h"
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
        bool databaseReady = false;
        if (BasicSettings::Get().ForceReconstructDatabase()) {
            databaseReady = database.Reconstruct(databasePath);
            database.CreateUser("NewUser");
        }
        else {
            databaseReady = database.Connect(databasePath);
        }
        if (databaseReady) {
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
    else {
        CoachBoard &board = CoachBoard::Get();
        m_coach = board.SelectDemo();
    }

    // If nothing else works, use stub:
    if (m_coach == NULL) {
        // if no user selected
        m_steps.push_back(
                std::shared_ptr<Step>(
                        new Step("Service",
                                 "Select User",
                                 ConfigureUserPageController::Get())));
    }
    else {
        m_coach->PrepareLesson();
        for (int i = 0; i < m_coach->GetCount(); ++i) {
            m_steps.push_back(
                    std::shared_ptr<Step>(
                            new Step(m_coach->GetStep(i).GetTaskType(),
                                     m_coach->GetStep(i).GetName(),
                                     ReadOnlyPageController::Get(
                                             m_coach->GetStep(i).GetPageInfo().GetTemplate(),
                                             m_style))));
        }
    }
}

void GuiModel::SelectStep(size_t i)
{
    if (i != m_selection) {
        emit selectionChanged(i, m_selection);
        m_selection = i;
    }
}

