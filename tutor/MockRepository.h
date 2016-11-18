#pragma once

#include "interface/IRepository.h"

class MockRepository : public IRepository,
                       private IRepository::IUser,
                       private IRepository::IProfile
{
public:
    static MockRepository& Get();

private:
    MockRepository();
    IUser* GetUser() { return this; }
    QString GetName() { return "Mock User"; }
    IProfile* GetProfile() { return this; }
    QString GetProfileName() { return "Mock Profile"; }
    QString GetLanguage() { return "Mock Language"; }
    QString GetCoach() { return "Standard"; }
    IStatistics* GetStatistics() { return NULL; }
    IBookmarks* GetBookmarks() { return NULL; }
    ILibrary* GetPersonalLibrary() { return NULL; }
};

