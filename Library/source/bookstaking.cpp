

#include "bookstaking.h"

#include <fstream>

amilib::BooksTaking::BooksTaking(std::string file_path)
	: filePath(file_path)
{
}

amilib::BooksTaking::~BooksTaking()
{
}

void amilib::BooksTaking::takeBook(int user_id, int book_id)
{
	std::fstream file(filePath, std::ios::app);
	file << user_id << ' ' << book_id << ' ' << 0 << "\n";
	file.close();
}

void amilib::BooksTaking::returnBook(int this_user_id, int this_book_id)
{
	bool done = false;
	std::fstream file(filePath, std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int userId;
		file >> userId;
		int bookId;
		file >> bookId;
		bool isReturned;
		file >> isReturned;
		if (file.fail())
		{
			break;
		}
		if (userId == this_user_id && bookId == this_book_id && !isReturned)
		{
			int pos = (int)file.tellg();
			file.seekp(pos - 1);
			file << 1;
			done = true;
			break;
		}
	}
	file.close();
	if (!done)
	{
		throw std::string("Taking of the book with id = '" + std::to_string(this_book_id) +
			"' by the user with id = '" + std::to_string(this_user_id) + "' was not found in file");
	}
}

void amilib::BooksTaking::fillAccount(Account& a)
{
	std::fstream file(filePath, std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int userId;
		file >> userId;
		int bookId;
		file >> bookId;
		bool isReturned;
		file >> isReturned;
		if (file.fail())
		{
			break;
		}
		if (userId == a.getId())
		{
			a.addBook(bookId, isReturned);
		}
	}
	file.close();
}

void amilib::BooksTaking::fillAllAccounts(std::unordered_map<int, amilib::Account>& users_map)
{
	bool skipped = false;
	std::ifstream file(filePath);
	while (!file.eof())
	{
		int userId;
		file >> userId;
		int bookId;
		file >> bookId;
		bool isReturned;
		file >> isReturned;
		if (file.fail())
		{
			break;
		}
		try
		{
			users_map.at(userId).addBook(bookId, isReturned);
		}
		catch (const std::exception&)
		{
			skipped = true;
		}
	}
	file.close();
	if (skipped)
	{
		throw std::string("One or more users from taking/returning were not found");
	}
}
