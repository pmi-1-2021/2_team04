#pragma once

#include "transactions.h"
#include "account.h"

#include <string>
#include <unordered_map>

namespace amilib
{
	class BooksTaking : public TakeReturnClient
	{
	public:
		BooksTaking(std::string file_path);
		virtual ~BooksTaking();
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
		void fillAccount(Account& a);
		void fillAllAccounts(std::unordered_map<int, amilib::Account>& users_map);
	private:
		std::string filePath;
	};
}