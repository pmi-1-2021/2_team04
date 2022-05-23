#include "booklist.h"

#include <iostream>

amilib::BookList::BookList(const std::vector<Book>& v)
	: bookVec(v),
	exit(false)
{
}

void amilib::BookList::draw()
{
	drawControlPanel();
	for (size_t i = 0; i < bookVec.size(); i++)
	{
		std::cout << "[" << i << "]\t" << bookVec[i].getTitle() << "\t\t\t\t\t\t"
			<< bookVec[i].getAuthor() << "\n";
	}
	if (bookVec.size() > 25)
	{
		drawControlPanelReverse();
	}
}

bool amilib::BookList::askId(int& id)
{
	std::cout << "\n > ";
	std::string user_input;
	do
	{
		std::cin >> user_input;
		if (user_input == "x")
		{
			return false;
		}
		else
		{
			try
			{
				id = bookVec.at(std::stoi(user_input)).getId();
				return true;
			}
			catch (const std::exception&)
			{
				std::cout << "\nEnter n at range from 0 to " << this->bookVec.size() - 1 << "\n > ";
			}
		}
	} while (true);
}

void amilib::BookList::drawControlPanel()
{
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "[x] return back\n[n] to select book\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "n\tTitle\t\t\t\t\t\tAuthor\n";
	std::cout << "----------------------------------------------------------------------------------------------\n";
}

void amilib::BookList::drawControlPanelReverse()
{
	std::cout << "----------------------------------------------------------------------------------------------\n";
	std::cout << "n\tTitle\t\t\t\t\t\tAuthor\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "[x] return back\n[n] to select book\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}
