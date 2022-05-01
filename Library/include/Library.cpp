// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<string>
//#include"menu.h"
//#include"user.h"

namespace amilib
{
    void login()
    {
        std::ifstream log_file;
        std::string partition = "";
        std::string account_type = "";
        std::string login = "";
        std::string password = "";

        log_file.open("..\\Test\\BusinessData\\booksInfo.txt");
        while (!log_file.eof())
        {
            log_file >> partition;
        }
        std::cout << partition << std::endl;
    }
}

int main()
{
    std::cout << "Hello World!\nishandry is here!";
    std::cout << std::endl;

    amilib::login();

    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
