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
    public:
        std::string m_modifier;
        std::string m_login;
        std::string m_password;
        std::vector<std::unordered_map<std::string, Book>::iterator> m_books_itervec;
        std::string GetLogin();
        std::string GetPassword();
        void SetLogin(std::string login);
        void SetPassword(std::string password);
        
    };
}