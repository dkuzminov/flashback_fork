#include "GuiModel.h"
#include "CoachBoard.h"

#include "Log.h"

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
    // Init database...
    // retrieve coach
    // for now the coach type is hardcoded
    {{
        CoachBoard &board = CoachBoard::Get();
        //board.Select("type", /*database* /);
        m_coach = board.SelectDemo();
    }}
    m_coach->PrepareLesson();
}

void GuiModel::SelectStep(size_t i)
{
    if (i != m_selection) {
        emit selectionChanged(i, m_selection);
        m_selection = i;
    }
}
