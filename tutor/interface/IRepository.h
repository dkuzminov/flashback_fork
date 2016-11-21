#pragma once

#include <QString>

struct IRepository
{
    struct IVariable
    {
        virtual QString GetValue() = 0;
    };

    // ToDo rename to Thesaurus
    struct ILanguage
    {
        virtual QString GetLanguageName() = 0;
        //virtual ILibrary& GetLibrary() = 0;
    };

    struct IPage
    {
        virtual QString GetHtml() = 0;
        //virtual IBook& GetBook() = 0;
    };

    struct IBook
    {
        virtual QString GetId() = 0;
    };

    struct ILibrary
    {
        virtual IBook* GetBook(QString id) = 0;
        virtual ILanguage& GetLanguage() = 0;
    };

    struct IBookmark
    {
        //virtual QString GetId() = 0;
        virtual IPage& GetPage() = 0;
    };

    struct IStatistics
    {
    };

/*    struct IBookmarks
    {
//        virtual size_t GetCount() = 0;
        virtual IBookmark* GetBookmark(QString id) = 0;
    };*/

    struct IProfile
    {
        virtual QString GetProfileName() = 0;
        virtual IVariable* GetVariable(QString name) = 0;
        virtual ILanguage& GetLanguage() = 0;
        virtual QString GetCoachType() = 0;
        virtual IStatistics* GetStatistics() = 0;
        virtual IBookmark* GetBookmark(QString id) = 0;
        // ToDo: Isolate Bookmarks and library into separate interface
        //virtual IBookmarks* GetBookmarks() = 0;
        virtual ILibrary& GetPersonalLibrary() = 0;
    };

    struct IUser
    {
        virtual QString GetName() = 0;
        virtual IProfile& GetProfile() = 0;
    };

    struct IUsers
    {
    };

    virtual IUser* GetUser() = 0;
    //virtual ILanguage* GetLanguage(QString language) = 0;
    //virtual ILibrary* GetLibrary(QString language) = 0;
};
