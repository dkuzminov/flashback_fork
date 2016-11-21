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

    // IUser:
    IUser* GetUser() { return this; }
    QString GetName() { return "Mock User"; }
    IProfile& GetProfile() { return *this; }

    // IProfile:
    QString GetProfileName() { return "Mock Profile"; }
    IVariable* GetVariable(QString name);
    ILanguage& GetLanguage() { throw "Not implemented"; }
    QString GetCoachType() { return "Naive"; }
    IStatistics* GetStatistics() { return NULL; }
    IBookmark* GetBookmark(QString id);
    ILibrary& GetPersonalLibrary() { throw "Not implemented"; }
};

