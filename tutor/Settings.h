#pragma once

typedef enum {green, blue, yellow} EColorScheme;

class HardcodedSettings
{
public:
    static bool IsDemoMode() { return true; }
    static bool IsShowMenu() { return false; }
    static bool IsShowToolbar() { return false; }
    static bool IsApplyStylesImmediately() { return true; }
    static EColorScheme GetColorScheme() { return green; }
};

class BasicSettings
{
public:
    static BasicSettings& Get();

public:
    bool IsDemoMode() { return m_isDemoMode; }
    bool IsShowMenu() { return m_isShowMenu; }
    bool IsShowToolbar() { return m_isShowToolbar; }
    bool IsApplyStylesImmediately() { return m_isApplyStylesImmediately; }
    EColorScheme GetColorScheme() { return m_colorScheme; }
private:
    BasicSettings();

    bool m_isDemoMode;
    bool m_isShowMenu;
    bool m_isShowToolbar;
    bool m_isApplyStylesImmediately;
    EColorScheme m_colorScheme;
};

