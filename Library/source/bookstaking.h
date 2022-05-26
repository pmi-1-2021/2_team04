#pragma once
#ifndef BOOKSTAKING_H
#define BOOKSTAKING_H



#include "idcreator.h"
#include "account.h"

#include <string>
#include <unordered_map>

namespace amilib
{
	class BooksTakingBase : public TakeReturnClient
	{
	public:
		BooksTakingBase(std::string file_path);
		virtual ~BooksTakingBase();
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
		void fillAccount(Account& a);
		void fillAllAccounts(std::unordered_map<int, amilib::Account>& users_map);
	private:
		std::string filePath;
	};
}
#endif // !BOOKSTAKING_H