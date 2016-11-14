#include "GuiModel.h"

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
}

void GuiModel::SelectStep(size_t i)
{
    if (i != m_selection) {
        emit selectionChanged(i, m_selection);
        m_selection = i;
    }
}
