#pragma once

#include <QString>

struct IRepository
{
    struct IBookmark
    {
    };

    struct IBookmarks
    {
        virtual size_t GetCount() = 0;
        virtual IBookmark* GetBookmark() = 0;
    };

    struct IStatistics
    {
    };

    struct ILibrary
    {
    };

    struct IProfile
    {
        virtual QString GetProfileName() = 0;
        virtual QString GetLanguage() = 0;
        virtual QString GetCoach() = 0;
        virtual IStatistics* GetStatistics() = 0;
        // ToDo: Isolate Bookmarks and library into separate interface
        virtual IBookmarks* GetBookmarks() = 0;
        virtual ILibrary* GetPersonalLibrary() = 0;
    };

    struct IUser
    {
        virtual QString GetName() = 0;
        virtual IProfile* GetProfile() = 0;
    };

    struct IUsers
    {
    };

    virtual IUser* GetUser() = 0;
};
