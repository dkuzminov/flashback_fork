#pragma once
#include <QString>

typedef enum {green, blue, yellow} EColorScheme;

class HardcodedSettings
{
public:
    static bool IsDemoMode() { return false; }
    static bool UseMockRepository() { return false; }
    static bool NeedShowMenu() { return false; }
    static bool NeedShowToolbar() { return false; }
    static bool NeedApplyStylesImmediately() { return true; }
    static bool ForceAutogenerateDatabase() { return false; }
    static EColorScheme GetColorScheme() { return green; }
    static QString GetDatabasePath() { return "<Hardcoded Path>"; }
};

class BasicSettings
{
public:
    static BasicSettings& Get();

public:
    bool IsDemoMode() { return m_isDemoMode; }
    bool UseMockRepository() { return m_useMockRepository; }
    bool NeedShowMenu() { return m_needShowMenu; }
    bool NeedShowToolbar() { return m_needShowToolbar; }
    bool NeedApplyStylesImmediately() { return m_needApplyStylesImmediately; }
    bool ForceAutogenerateDatabase() { return m_forceAutogenerateDatabase; }
    EColorScheme GetColorScheme() { return m_colorScheme; }
    QString GetDatabasePath() { return m_databasePath; }
private:
    BasicSettings();

    bool m_isDemoMode;
    bool m_useMockRepository;
    bool m_needShowMenu;
    bool m_needShowToolbar;
    bool m_needApplyStylesImmediately;
    bool m_forceAutogenerateDatabase;
    EColorScheme m_colorScheme;
    QString m_databasePath;
};

