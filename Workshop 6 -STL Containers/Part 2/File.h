#pragma once
#include "Resource.h"

namespace seneca
{
	class File : public Resource
	{
		//std::string m_filename{};
		std::string m_contents{};
	public:
		File() {};
		//a custom constructor that receives two strings as parameters
		File(const std::string& filename, const std::string & content = "");

		//define the pure virtual functions inherited from the base class
		//sets the parent path to the parameter
		void update_parent_path(const std::string&);
		//a query that returns the name of the file.
		std::string name() const;
		//a query that returns - 1.
		int count() const;
		//a query that returns the full absolute path of the file (concatenates the absolute path location and the file name).
		std::string path() const;
		//a query that returns the size of the file in bytes.For simplicity, this is the number of characters in m_contents attribute.
		size_t size() const;
		//a query that returns Flags::FILE.
		NodeType type() const;
	


	};
}