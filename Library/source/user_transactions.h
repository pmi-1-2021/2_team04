#pragma once
#ifndef USER_TRANSACTIONS_H
#define USER_TRANSACTIONS_H

#include "global_transactions.h"


namespace amilib
{
	class AddUserTransaction : public GlobalFileTransaction
	{
	public:
		AddUserTransaction(int by_id, Account new_acc, std::vector<UsersChangesClient*>);
		virtual void execute();
		//todo : private:
		static IdCreator* ids;
	private:
		int byId;
		int userId;
		Account toAdd;
		std::vector<UsersChangesClient*> usersChangesClients;
	};

	class CreateAddUserTransaction : public CreateTransaction
	{
	public:
		CreateAddUserTransaction(Account new_acc);
		virtual GlobalFileTransaction* createBy(int id);
	private:
		Account newAcc;
	};

	class ChangeUserInfoTransaction : public GlobalFileTransaction
	{
	public:
		ChangeUserInfoTransaction(int by_id, int user_id, Account existing_acc, std::vector<UsersChangesClient*>);
		virtual void execute();
	private:
		int byId;
		int userId;
		Account toChange;
		std::vector<UsersChangesClient*> usersChangesClients;
	};

	class CreateChangeUserInfoTransaction : public CreateTransaction
	{
	public:
		CreateChangeUserInfoTransaction(int id, Account existing_acc);
		virtual GlobalFileTransaction* createBy(int id);
	private:
		int UserId;
		Account toChange;
	};
}
#endif //!USER_TRANSACTIONS_H