// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Error smth... ... v143 or v142 build tools: try to switch Project properties -> configuration properties -> general -> platform toolset v143 to v142 or reverse
//Try to leave comments to near confusing part of code pls
//The signature like 'IClass' means Interface of class with the 'Class' logic name; all methods should be deleted (virtual void foo() = 0;)
//All the .cpp and .h should be in 'Library/source/' folder 
//If you need to work with specific files as a part of project, add them as the existing items to that project
//Do not use 'using namespace'

#include <iostream>
#include<fstream>
#include<string>
//#include"menu.h"
#include"user.h"

namespace amilib
{

    //todo: read log file from the begin without reopening stream 
    void relog(std::ifstream& _log_file, std::string _new_user_login, Account& _account_info_block)
    {
        //while (!_log_file.eof())
        //{
        //    log_file >> _account_info_block.m_account_type >> _account_info_block.m_login >> _account_info_block.m_password;
        //    if (_account_info_block.m_login == user_login)
        //    {
        //        break;
        //    }
        //}
    }

    bool log_in(/*IMenu* _menu_interface*/)
    {
        bool logged_in = true;
        std::cout << "Enter your username: ";
        std::string user_login;
        std::cin >> user_login;

        Account acc;

        std::ifstream log_file;

        log_file.open("..\\BusinessData\\logInfo.txt");
        std::cout << log_file.is_open() << std::endl; //debug
        while (!log_file.eof())
        {
            log_file >> acc.m_modifier >> acc.m_login >> acc.m_password;
            if (acc.m_login == user_login)
            {
                break;
            }
        }
        while (acc.m_login != user_login)
        {
            std::cout << "Account not found" << std::endl << "Press [r] to try again; [x] to exit :" << std::endl;
            char key;
            std::cin >> key; //todo: validation
            if (key == 'r')
            {
                std::cout << "Enter your username: ";
                std::cin >> user_login;
                relog(log_file, user_login, acc);
            }
            else if (key == 'x')
            {
                logged_in = false;
                return logged_in;
            }
        }
        //todo: create new menu with proper rights of account that is loggin in
        std::cout << acc.m_password << std::endl;
        return logged_in;
    }
}

bool sign_up()
{
    //todo:
    //ask a username
    //ensure that username are still not used by another user ( "..\\BusinessData\\logInfo.txt" )
    //add new line with account of type user
    //return to start menu
}

int main()
{
    std::cout << "Hello World!\nishandry is here!";
    std::cout << std::endl;

    amilib::log_in();

    system("pause");
}

