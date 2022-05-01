#pragma once

namespace amiliv
{
	class IMenu
	{
	public:
		void callMain(size_t _number) = 0;
		void drawMain() = 0;
		void callBookList() = 0;
		void drawBookList() = 0;
	private:

	};
}