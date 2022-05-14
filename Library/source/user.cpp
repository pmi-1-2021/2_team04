#include"user.h"

namespace amilib
{
    std::string Account::GetLogin()
    {
        return m_login;
    }
    std::string Account::GetPassword()
    {
        return m_password;
    }

    void Account::SetLogin(std::string login)
    {
        this->m_login = login;
    }

    void Account::SetPassword(std::string password)
    {
        this->m_password = password;
    }

}
