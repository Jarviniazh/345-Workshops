#pragma once
#include <vector>

#include "Resource.h"

namespace seneca
{
		class Directory: public Resource
		{
			std::vector<Resource*>m_contents;
		public:
			//a custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
			Directory(const std::string& name);
			//sets the parent path to the parameter.
			void update_parent_path(const std::string&);
			//a query that returns Flags::DIR.
			NodeType type() const;
			//a query that returns the full absolute path of the directory
			std::string path() const;
			//a query that returns the name of the directory.
			std::string name() const;
			//a query that returns the number of resources that this directory holds.
			int count() const;
			// a query that returns the size of the directory in bytes.
			size_t size() const;
			//adds a resource to the directory and returns a reference to the current directory. 
			Directory& operator+=(Resource*);
			//finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found. 
			Resource* find(const std::string&, const std::vector<OpFlags>& flag = {});
			//a destructor that deallocates memory for each resource that this directory holds.
			~Directory();
			//this class should not allow copy / move operations.
			Directory(const Directory&) = delete;
			Directory(Directory&&) = delete;
			Directory& operator=(const Directory&) = delete;
			Directory& operator=(Directory&&) = delete;
		};
}