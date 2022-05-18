#pragma once

#include<string>
#include<vector>




namespace amilib
{
    class Account
    {
    public:
        Account();
        Account(int _id, std::string _role, std::string _login, std::string _password);
        ~Account();
        int getId();
        std::string getRole();
        std::string getLogin();
        std::string getPassword();
        void setId(int);
        void setRole(std::string role);
        void setLogin(std::string login);
        void setPassword(std::string password);
        void addBook(int id);
        void removeBook(int id);
        bool hasABook(int book_id);
        std::vector<int> acc_books;
    private:
        int id;
        std::string role;
        std::string login;
        std::string password;
    };
}