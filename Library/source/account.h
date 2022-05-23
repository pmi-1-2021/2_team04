#pragma once


#include<vector>
#include<string>




namespace amilib
{
    class Account
    {
    public:
        Account();
        Account(int _id, std::string _role, std::string _login, std::string _password);
        ~Account();
        int getId() const;
        std::string getRole() const;
        std::string getUsername() const;
        std::string getPassword() const;
        void setId(int);
        void setRole(std::string role);
        void setUsername(std::string _username);
        void setPassword(std::string _password);
        void addBook(int id, bool returned);
        void returnBook(int id);
        bool hasABook(int book_id) const;
        std::vector<std::pair<int, bool>> acc_books;
    private:
        int id;
        std::string role;
        std::string username;
        std::string password;
    };
}