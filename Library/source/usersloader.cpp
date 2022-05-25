#include "infoLoaders.h"

#include <iostream>
#include <fstream>




amilib::UsersLoader::UsersLoader()
{

}

amilib::UsersLoader::~UsersLoader()
{
	//todo
}


void amilib::UsersLoader::pull(std::unordered_map<int, amilib::Account> &users_map)
{
	std::ifstream file("..\\BusinessData\\users.txt");
	while (!file.eof())
	{
		int id;
		file >> id;
		std::string role;
		file >> role;
		std::string login;
		file >> login;
		std::string password;
		file >> password;

		users_map.emplace(std::make_pair(id, Account(id, role, login, password)));
	}
}

void amilib::UsersLoader::addItem(amilib::Account acc)
{
	std::fstream file("..\\BusinessData\\users.txt", std::ios::out | std::ios::app);
	file << "\n" << acc.getId() << ' ' << acc.getRole() << ' ' << acc.getUsername() << ' ' << acc.getPassword();
	file.close();
}
