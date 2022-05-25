#pragma once

#include "book.h"
#include "account.h"

#include<unordered_map>




namespace amilib
{
	class BooksLoader
	{
	public:
		BooksLoader();
		~BooksLoader();
		void pull(std::unordered_map<int, Book>& books_map);
		//todo
		//void push();
		void addItem(Book b);
		//void deleteItem();
		//
	};

	class UsersLoader
	{
	public:
		UsersLoader();
		~UsersLoader();
		//std::unordered_map<int, amilib::Account> users_map;
		void pull(std::unordered_map<int, amilib::Account>& users_map);
		//todo
		//void push();
		void addItem(Account acc);
		//void deleteIte);m(
		//
	};
}
