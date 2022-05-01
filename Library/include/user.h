#pragma once
#include<string>
#include<map>
#include<set>
#include"infoLoaders.h"
#include"book.h"

namespace amilib
{
    class Account
    {
    private:
        std::string login;
        std::string password;
        std::map<std::string, std::set<Book>> user_books;
    public:
        std::string GetLogin();
        std::string GetPassword();
        void SetLogin(std::string login);
        void SetPassword(std::string password);
        
    };
}