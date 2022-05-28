#include "database.h"

#include <fstream>
#include <iostream>
#include <map>


amilib::UsersDataBase::UsersDataBase(std::string info_file_path)
	:infoFilePath(info_file_path)
{
}

amilib::UsersDataBase::~UsersDataBase()
{
	//todo
}

void amilib::UsersDataBase::changeUserInfo(int user_id, Account new_info)
{
	std::map<int, Account> users;
	std::ifstream file(infoFilePath);
	while (!file.eof())
	{
		Account a;
		file >> a;
		users[a.getId()] = a;
	}
	file.close();
	try
	{
		users.at(user_id) = new_info;
	}
	catch (const std::exception&)
	{
		throw std::string("User with id = " + std::to_string(user_id) + "not found. Can not change info");
	}
	std::ofstream overwtire;
	overwtire.open(infoFilePath);
	for (std::map<int, Account>::iterator it = users.begin();
		it != users.end(); it++)
	{
		overwtire << it->second << "\n";
	}
	overwtire.close();
}


void amilib::UsersDataBase::addNewUser(Account a)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::app);
	file << a.getId() << ' ' << a.getRole() << ' ' << a.getUsername()
		<< ' ' << a.getPassword() << "\n";
	file.close();
}

int amilib::UsersDataBase::createId()
{
	//read file backwards untill begining of the last line(id)
	std::ifstream file(infoFilePath);
	file.seekg(-3, std::ios_base::end);// skip last /n
	char ch;
	bool keepLooping = true;
	while (keepLooping) {
		file.get(ch);

		if ((int)file.tellg() <= 1) {
			file.seekg(0);
			keepLooping = false;
		}
		else if (ch == '\n') {
			keepLooping = false;
		}
		else {
			file.seekg(-2, std::ios_base::cur);
		}
	}
	int lastId;
	file >> lastId;
	file.close();
	return ++lastId;
}

void amilib::UsersDataBase::pull(std::unordered_map<int, amilib::Account> &users_map)
{
	std::ifstream file(infoFilePath);
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
		Account a(role, login, password);
		a.setId(id);
		users_map.emplace(std::make_pair(id, a));
	}
}

bool amilib::UsersDataBase::isExist(std::string username)
{
	bool exist = false;
	std::ifstream file(infoFilePath);
	while (!file.eof())
	{
		int skipId;
		file >> skipId;
		std::string skipRole;
		file >> skipRole;
		std::string usernameInFile;
		file >> usernameInFile;
		if (usernameInFile == username)
		{
			exist = true;
			break;
		}
		std::string skipPassword;
		file >> skipPassword;
	}
	file.close();
	return exist;
}

//void amilib::UsersLoader::addItem(amilib::Account acc)
//{
//	std::fstream file(infoFilePath, std::ios::out | std::ios::app);
//	file << "\n" << acc.getId() << ' ' << acc.getRole() << ' ' << acc.getUsername() << ' ' << acc.getPassword();
//	file.close();
//}
