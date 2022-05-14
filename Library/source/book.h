#pragma once
#include <iostream>
#include <vector>
#include <fstream>

namespace amilib
{
	class Book
	{
		bool m_available;
		std::string m_title;
		std::string m_author;
		size_t m_size;
		std::string m_userOwner;
		std::string m_filePath;
	public:
		Book(bool _is_available, std::string _name, std::string _author, size_t _size, std::string _user_owner, std::string _filePath);
		bool get_availability();
		size_t get_size();
		std::string get_title();
		std::string get_author();
		void set_availability(bool _is_available);
		void set_owner(std::string _user_owner);
		std::string get_path();
		friend std::istream& operator>>(std::istream& in, Book& book);
		friend std::ostream& operator<<(std::ostream& out, Book& book);
	};

	class IReader
	{
	protected:
	public:
		IReader(std::string _file_path); //initialize m_lines with the lines of file
		virtual ~IReader();
		virtual void pull_book() = 0;
		virtual void print_book() = 0;
	};

	class IEditor : public IReader
	{
	public:
		virtual ~IEditor();
		virtual void print_lines() = 0;
		virtual void add_line() = 0;
		virtual void delete_line() = 0;
		virtual void edit_line(size_t _line_number) = 0;
		virtual void delete_content() = 0;
		virtual void save() = 0;
	};

	class BookText : public IEditor
	{
		std::string m_filePath;
		std::vector<std::string> m_lines;
	public:
		BookText(std::string _file_path);
		virtual ~BookText();
		void pull_book();
		void print_book();
		void print_lines();
		void add_line();
		void delete_line();
		void edit_line(size_t _line_number);
		void delete_content();
		void save();
	};


}