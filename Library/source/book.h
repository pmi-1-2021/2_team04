#pragma once

#include <string>



namespace amilib
{
	class Book
	{
	private:
		int id;
		size_t ammount;
		std::string title;
		std::string author;
		size_t size;
		std::string fileName;
	public:
		Book(int _id, size_t _ammount, std::string _title, std::string _author, size_t _size, std::string _fileName);
		int getId();
		size_t getAmmount();
		size_t getSize();
		std::string getTitle();
		std::string getAuthor();
		std::string getFileName();
		void setAmmount(size_t new_ammount);
	};


	//todo :
	//solution for reading the book and editing lines of the book for admin role only
	//functions, constructors and methods should be called in amilib::menu::selectBook() 


	//class IReader
	//{
	//protected:
	//public:
	//	IReader(std::string _file_path); //initialize m_lines with the lines of file
	//	virtual ~IReader();
	//	virtual void pull_book() = 0;
	//	virtual void print_book() = 0;
	//};

	//class IEditor : public IReader
	//{
	//public:
	//	virtual ~IEditor();
	//	virtual void print_lines() = 0;
	//	virtual void add_line() = 0;
	//	virtual void delete_line() = 0;
	//	virtual void edit_line(size_t _line_number) = 0;
	//	virtual void delete_content() = 0;
	//	virtual void save() = 0;
	//};

	//class BookText : public IEditor
	//{
	//	std::string m_filePath;
	//	std::vector<std::string> m_lines;
	//public:
	//	BookText(std::string _file_path);
	//	virtual ~BookText();
	//	void pull_book();
	//	void print_book();
	//	void print_lines();
	//	void add_line();
	//	void delete_line();
	//	void edit_line(size_t _line_number);
	//	void delete_content();
	//	void save();
	//};


}