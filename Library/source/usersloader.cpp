#include "infoLoaders.h"

#include <iostream>
#include <fstream>




amilib::UsersLoader::UsersLoader()
{
	pull();
}

amilib::UsersLoader::~UsersLoader()
{
	//todo
}


void amilib::UsersLoader::pull()
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

		this->users_map.emplace(std::make_pair(id, Account(id, role, login, password)));
	}
}
