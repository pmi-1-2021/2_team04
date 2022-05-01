#include"user.h"

namespace amilib
{
    std::string Account::GetLogin()
    {
        return login;
    }
    std::string Account::GetPassword()
    {
        return password;
    }

    void Account::SetLogin(std::string login)
    {
        this->login = login;
    }

    void Account::SetPassword(std::string password)
    {
        this->password = password;
    }

}
