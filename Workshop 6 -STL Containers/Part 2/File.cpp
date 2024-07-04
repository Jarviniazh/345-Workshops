#include <iostream>
#include "File.h"
#include "Flags.h"

namespace seneca
{
	//a custom constructor that receives two strings as parameters
	File::File(const std::string& filename, const std::string& content) :m_contents(content)
	{
		m_name = filename;
	};

	//define the pure virtual functions inherited from the base class
	//sets the parent path to the parameter
	void File::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
	}
	//a query that returns the name of the file.
	std::string File::name() const
	{
		return m_name;
	}
	//a query that returns - 1.
	int File::count() const
	{
		return -1;
	}
	//a query that returns the full absolute path of the file (concatenates the absolute path location and the file name).
	std::string File::path() const
	{
		return m_parent_path + m_name;
	}

	//a query that returns the size of the file in bytes.For simplicity, this is the number of characters in m_contents attribute.
	size_t File::size() const
	{
		return m_contents.size();
	}
	//a query that returns Flags::FILE.
	NodeType File::type() const
	{
		return NodeType::FILE;
	}
}
