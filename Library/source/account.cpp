#include "account.h"


#include<iostream>


namespace amilib
{
    Account::Account(std::string _role, std::string _username, std::string _password)
        : id(0),
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
    std::istream& operator>>(std::istream& in, Account& a)
    {
        in >> a.id >> a.role >> a.username >> a.password;
        return in;
    }
    std::ostream& operator<<(std::ostream& out, Account& a)
    {
        out << a.id << a.role << a.username << a.password;
        return out;
    }
}
