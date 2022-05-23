#pragma once

#include "book.h"

#include <vector>

namespace amilib
{
	class BookList
	{
	public:
		BookList(const std::vector<Book>&);
		void draw();
		bool askId(int& id);
	private:
		bool exit;
		std::vector<Book> bookVec;
		void drawControlPanel();
		void drawControlPanelReverse();
	};
}