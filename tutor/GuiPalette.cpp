#include "GuiPalette.h"
#include "Settings.h"

GuiPalette& GuiPalette::Get()
{
    static GuiPalette instance;
    return instance;
}

GuiPalette::GuiPalette(QObject *parent) : QObject(parent)
{
    m_widget = new QWidget(NULL);
    setupUi(m_widget);
}

QPalette GuiPalette::GetPalette()
{
    switch (BasicSettings::Get().GetColorScheme()) {
    case EColorScheme::green:
        return green->palette();
    case EColorScheme::blue:
        return blue->palette();
    case EColorScheme::yellow:
        return yellow->palette();
    default:
        return green->palette();
    }
}
