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
        std::string getUsername();
        std::string getPassword();
        void setId(int);
        void setRole(std::string role);
        void setUsername(std::string _username);
        void setPassword(std::string _password);
        void addBook(int id);
        void removeBook(int id);
        bool hasABook(int book_id);
        std::vector<int> acc_books;
    private:
        int id;
        std::string role;
        std::string username;
        std::string password;
    };
}