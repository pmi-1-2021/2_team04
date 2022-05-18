#pragma once

#include "book.h"
#include "account.h"

#include<unordered_map>




namespace amilib
{
	class InfoLoader
	{
	public:
		virtual void pull() = 0;
		//virtual void push() = 0;
		//virtual void addItem() = 0;
		//virtual void deleteItem() = 0;
	private:

	};

	class BooksLoader : public InfoLoader
	{
	public:
		BooksLoader();
		~BooksLoader();
		std::unordered_map<int, Book> books_map;
		void pull();
		//todo
		//void push();
		//void addItem();
		//void deleteItem();
		//
	};

	class UsersLoader : public InfoLoader
	{
	public:
		UsersLoader();
		~UsersLoader();
		std::unordered_map<int, amilib::Account> users_map;
		void pull();
		//todo
		//void push();
		//void addItem();
		//void deleteItem();
		//
	};
}
