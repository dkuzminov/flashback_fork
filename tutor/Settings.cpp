#include "Settings.h"

BasicSettings& BasicSettings::Get()
{
    static BasicSettings instance;
    return instance;
}

BasicSettings::BasicSettings()
    : m_isDemoMode(HardcodedSettings::IsDemoMode()),
      m_useMockRepository(HardcodedSettings::UseMockRepository()),
      m_needShowMenu(HardcodedSettings::NeedShowMenu()),
      m_needShowToolbar(HardcodedSettings::NeedShowToolbar()),
      m_needApplyStylesImmediately(HardcodedSettings::NeedApplyStylesImmediately()),
      m_colorScheme(HardcodedSettings::GetColorScheme()),
      m_databasePath(HardcodedSettings::GetDatabasePath())
{
}
