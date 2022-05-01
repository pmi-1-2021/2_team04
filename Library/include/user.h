#pragma once
#include<string>
#include"infoLoaders.h"

namespace amilib
{
    class Account
    {
    private:
        std::string login;
        std::string password;
        UserMapLoader user_list;
    public:
        std::string GetLogin();
        std::string GetPassword();
        void SetLogin(std::string login);
        void SetPassword(std::string password);
    };
}