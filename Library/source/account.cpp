#include"account.h"



namespace amilib
{
    Account::Account(int _id, std::string _role, std::string _username, std::string _password)
        : id(_id),
        role(_role),
        username(_username),
        password(_password)
    {
        acc_books.resize(0);
    }
    Account::~Account()
    {
    }
    Account::Account()
        : id(-1),
        role("unknown"),
        username("Log in to start reading with Amilib\nIf you dont have an account, create it now!"),
        password("-")
    {
        acc_books.resize(0);
    }
    int Account::getId() const
    {
        return id;
    }
    std::string Account::getRole() const
    {
        return role;
    }
    std::string Account::getUsername() const
    {
        return username;
    }
    std::string Account::getPassword() const
    {
        return password;
    }

    void Account::setId(int _id)
    {
        id = _id;
    }

    void Account::setRole(std::string _role)
    {
        role = _role;
    }

    void Account::setUsername(std::string _username)
    {
        username = _username;
    }

    void Account::setPassword(std::string _password)
    {
        password = _password;
    }

    void Account::addBook(int id, bool returned)
    {
        this->acc_books.emplace_back(id, returned);
    }
    void Account::returnBook(int id)
    {
        auto it = this->acc_books.begin();
        for (it; it != this->acc_books.end(); it++)
        {
            if (it->first == id)
            {
                break;
            }
        }
        it->second = true;
    }
    bool Account::hasABook(int book_id) const
    {
        bool has = false;
        for (auto &pair : this->acc_books)
        {
            if (book_id == pair.first && pair.second == false)
            {
                has = true;
            }
        }
        return has;
    }
}
