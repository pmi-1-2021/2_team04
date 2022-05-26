#include "user_transactions.h"
#include "idcreator.h"

namespace amilib
{
	IdCreator* AddUserTransaction::ids = nullptr;

	AddUserTransaction::AddUserTransaction(int by_id, Account new_acc, std::vector<UsersChangesClient*> ucc_vec)
		:byId(by_id),
		userId(0),
		toAdd(new_acc),
		usersChangesClients(ucc_vec)
	{
	}
	void AddUserTransaction::execute()
	{
		this->toAdd.setId(ids->createId());
		for (UsersChangesClient* c : this->usersChangesClients)
		{
			c->addNewUser(this->toAdd);
		}
	}
	CreateAddUserTransaction::CreateAddUserTransaction(Account new_acc)
		:newAcc(new_acc)
	{
	}
	ChangeUserInfoTransaction::ChangeUserInfoTransaction(int by_id, int user_id, Account changes, std::vector<UsersChangesClient*> ucc_vec)
		: byId(by_id),
		userId(user_id),
		toChange(changes),
		usersChangesClients(ucc_vec)
	{
	}
	void ChangeUserInfoTransaction::execute()
	{
	}
	Transaction* CreateAddUserTransaction::createBy(int id)
	{
		Transaction* t = new AddUserTransaction(id, newAcc,
			CreateTransaction::getUsersChangesClients());
		return t;
	}
	CreateChangeUserInfoTransaction::CreateChangeUserInfoTransaction(int id, Account existing_acc)
	{
	}
	Transaction* CreateChangeUserInfoTransaction::createBy(int id)
	{
		return nullptr;
	}
}