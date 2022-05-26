#include "book_transactions.h"
#include "idcreator.h"
#include "book.h"

namespace amilib
{
	IdCreator* AddBookTransaction::ids = nullptr;

	AddBookTransaction::AddBookTransaction(int by_id, Book new_book, std::vector<BooksChangesClient*> bccVec)
		:byId(by_id),
		newBook(new_book),
		booksChangesClients(bccVec)
	{
	}

	void AddBookTransaction::execute()
	{
		this->newBook.setId(ids->createId());
		for (BooksChangesClient* c : this->booksChangesClients)
		{
			c->addNewBook(this->newBook);
		}
	}

	amilib::CreateAddBookTransaction::CreateAddBookTransaction(Book new_book)
		: toAdd(new_book)
	{
	}

	Transaction* CreateAddBookTransaction::createBy(int id)
	{
		Transaction* t = new AddBookTransaction(id ,toAdd, 
			CreateTransaction::getBooksChangesClients());
		return t;
	}

	amilib::ChangeBookInfoTransaction::ChangeBookInfoTransaction(int by_id, int book_id, Book changes, std::vector<BooksChangesClient*> bcc_vec)
		:byId(by_id),
		bookId(book_id),
		toChange(changes),
		booksChangesClients(bcc_vec)
	{
	}

	void amilib::ChangeBookInfoTransaction::execute()
	{
		for (BooksChangesClient* c : this->booksChangesClients)
		{
			c->changeBookInfo(bookId,toChange);
		}
	}

	amilib::CreateChangeBookInfoTransaction::CreateChangeBookInfoTransaction(int book_id, Book changes)
		:bookId(book_id),
		changedBook(changes)
	{
	}

	amilib::Transaction* amilib::CreateChangeBookInfoTransaction::createBy(int id)
	{
		Transaction* t = new ChangeBookInfoTransaction(id, bookId, changedBook,
			CreateTransaction::getBooksChangesClients());
		return t;
	}

	amilib::TakeBookTransaction::TakeBookTransaction(int user_id, int book_id, std::vector<TakeReturnClient*> trc_vec)
		:userId(user_id),
		bookId(book_id),
		takeReturnClients(trc_vec)
	{
	}

	void amilib::TakeBookTransaction::execute()
	{
		for (TakeReturnClient* c : this->takeReturnClients)
		{
			c->takeBook(userId, bookId);
		}
	}

	amilib::CreateTakeBookTransaction::CreateTakeBookTransaction(int book_id)
		:bookId(book_id)
	{
	}

	Transaction* amilib::CreateTakeBookTransaction::createBy(int id)
	{
		Transaction* t = new TakeBookTransaction(id, bookId,
			CreateTransaction::getTakeReturnClients());
		return t;
	}

	amilib::ReturnBookTransaction::ReturnBookTransaction(int user_id, int book_id, std::vector<TakeReturnClient*> trc_vec)
		:userId(user_id),
		bookId(book_id),
		takeReturnClients(trc_vec)
	{
	}

	void ReturnBookTransaction::execute()
	{
		for (TakeReturnClient* c : this->takeReturnClients)
		{
			c->returnBook(userId, bookId);
		}
	}

	CreateReturnBookTransaction::CreateReturnBookTransaction(int book_id)
		:bookId(book_id)
	{
	}

	Transaction* amilib::CreateReturnBookTransaction::createBy(int id)
	{
		Transaction* t = new ReturnBookTransaction(id, bookId,
			CreateTransaction::getTakeReturnClients());
		return t;
	}

}
