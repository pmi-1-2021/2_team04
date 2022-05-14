#pragma once
#include <iostream>
#include<unordered_map>
#include <set>
#include "book.h"
#include "user.h"

namespace amilib
{
	class InfoLoader
	{
	public:
		virtual void pull() = 0;
		virtual void push() = 0;
		virtual void addItem() = 0;
		virtual void deleteItem() = 0;
	private:

	};

	class BooksLoader : public InfoLoader
	{
	public:
		std::unordered_map<std::string, Book> m_books_map;
		std::vector<std::unordered_map<std::string, Book>::iterator> m_available_books_itervec;
		std::vector<std::unordered_map<std::string, Book>::iterator> m_not_available_books_itervec;
		void pull();
		void push();
		void addItem();
		void deleteItem();
	};

	class UsersLoader : public InfoLoader
	{
	public:
		std::unordered_map<std::string, Account> m_users_map;
		void pull();
		void push();
		void addItem();
		void deleteItem();
	};
}
