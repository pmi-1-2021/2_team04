#pragma once
#include <iostream>
#include<map>
#include <set>
#include "book.h"
#include "user.h"

namespace amilib
{
	class MapLoader
	{
	public:
		virtual void pull() = 0;
		virtual void push() = 0;
	private:

	};

	class LibBookMapLoader : public MapLoader
	{
		std::map<std::string, std::set<Book>> books;
		std::string path;
	public:
		void pull();
		void push();
	};

	class UserMapLoader : public MapLoader
	{
		//std::map<std::string, User> users;
		std::string path;
	public:
		void pull();
		void push();
	};
}
