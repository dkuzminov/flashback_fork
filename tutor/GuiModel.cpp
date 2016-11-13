#include "GuiModel.h"

#include "Log.h"

GuiModel& GuiModel::Get()
{
    static GuiModel instance;
    return instance;
}

GuiModel::GuiModel()
{
    LOG(Note, "Enter GuiModel::GuiModel()");
}

void GuiModel::Start()
{
}
