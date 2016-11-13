#include "Settings.h"

BasicSettings& BasicSettings::Get()
{
    static BasicSettings instance;
    return instance;
}

BasicSettings::BasicSettings()
    : m_isDemoMode(HardcodedSettings::IsDemoMode()),
      m_isShowMenu(HardcodedSettings::IsShowMenu()),
      m_isShowToolbar(HardcodedSettings::IsShowToolbar()),
      m_isApplyStylesImmediately(HardcodedSettings::IsApplyStylesImmediately()),
      m_colorScheme(HardcodedSettings::GetColorScheme())
{
}
