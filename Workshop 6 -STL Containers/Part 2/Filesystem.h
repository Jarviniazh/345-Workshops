#pragma once
#include "Directory.h"
namespace seneca
{
	class Filesystem
	{
		// a pointer to the root directory of the filesystem.
		Directory* m_root{};
		//a pointer to the current working directory in the filesystem from where operations are performed.
		Directory* m_current{};
	public:
		Filesystem() {};
		//a custom constructor that receives the name of a file as its first argument, and an optional string containing the name of the root directory (defaults to an empty string).
		Filesystem(const std::string&, const std::string& root = {});

		//this module does not allow copy operations. Make sure they are deleted.
		Filesystem(const Filesystem&) = delete;
		Filesystem& operator=(const Filesystem&) = delete;
		
		//this module supports move operations.
		Filesystem(Filesystem&&);
		Filesystem& operator=(Filesystem&&);

		//adds a resource to the current directory.
		Filesystem& operator+=(Resource*); 
		//changes the current directory to the directory(located in the current directory) whose name matches argument.
		Directory* change_directory(const std::string& dirname ={});
		//a query that returns the current directory.
		Directory* get_current_directory() const;
		//a destructor that deallocates memory for the root directory.
		~Filesystem();

		std::string removeSpace(const std::string& str);

	};
}
