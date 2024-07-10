#include <iostream>
#include <string>
#include <algorithm>
#include "Directory.h"
#include "Flags.h"


namespace seneca
{
	//a custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
	Directory::Directory(const std::string& name)
	{
		m_name = name;
		//Debugging
		//std::cout << "----------------------------------------------\n";
		//std::cout << "Creating Directory with name: " << name << std::endl;
	}

	//sets the parent path to the parameter.
	void Directory::update_parent_path(const std::string& newpath)
	{
		m_parent_path = newpath;
		//For each resource that this directory holds, this member should also set their absolute path locations to the full absolute path of this directory.
		for (auto& res : m_contents) {
			res->update_parent_path(path());  
		}
	}

	//a query that returns Flags::DIR.
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}

	//a query that returns the full absolute path of the directory
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}

	//a query that returns the name of the directory.
	std::string Directory::name() const
	{
		return m_name;
	}

	//a query that returns the number of resources that this directory holds.
	int Directory::count() const
	{
		return m_contents.size();
	}

	// a query that returns the size of the directory in bytes.
	size_t Directory::size() const
	{
		if (!m_contents.empty())
		{
			size_t totalSize{};
			for(auto& res: m_contents)
				totalSize += res->size();
			return totalSize;
		}
		return 0u;
	}

	//adds a resource to the directory and returns a reference to the current directory. 
	Directory& Directory::operator+=(Resource* res)
	{
		//if a match is found, throw and exception and do nothing else;
		for (auto& resource : m_contents) {
			if (resource->name() == res->name()) {
				throw "Resource already exists in the directory";
			}
		}
		//if no match is found, add the resource and update the absolute path location of the added resource with the directory's full absolute path.
		m_contents.push_back(res);
		res->update_parent_path(path());  
		return *this;
	}

	//finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found. 
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
	{
		//if the RECURSIVE flag is in the second parameter
		//bool isRecursive = false;
		//for (auto flag: flags)
		//{
		//	if (flag == OpFlags::RECURSIVE)
		//	{
		//		isRecursive = true;
		//		break;
		//	}
		//}

		bool isRecursive = std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end(); //using algorithm


		for (auto& res : m_contents) {
			if (res->name() == name) {
				return res;
			}
			//if the RECURSIVE flag is in the second parameter, this member will also attempt to recursively find a match in each directory that is in the m_contents vector.
			if (isRecursive && res->type() == NodeType::DIR) {
				Directory* dir = dynamic_cast<Directory*>(res);

				if (dir != nullptr) {
					Resource* found = dir->find(name, flags);
					if (found != nullptr) 
						return found;
				}
			}
		}
		return nullptr;
	}

	//a destructor that deallocates memory for each resource that this directory holds.
	Directory::~Directory()
	{
		//Debugging
		//std::cout << "----------------------------------------------\n";
		//std::cout << "Destroying Directory with name: " << m_name << std::endl;
		for (auto& res : m_contents) {
			delete res;
		}
	}

	//Part 2
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
	{
		bool isRecursive = std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end();

		for (auto member = m_contents.begin(); member != m_contents.end(); ++member) 
		{
			if ((*member)->name() == name) 
			{
				if ((*member)->type() == NodeType::DIR && !isRecursive) 
					throw std::invalid_argument("Trying to remove a directory without passing the recursive flag.");
				delete* member;
				m_contents.erase(member);
				return; 
			}
		}

		throw name + " does not exist in " + m_name;
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const
	{
		os << "Total size: " << size() << " bytes" << std::endl;

		//bool isLong = false;
		//for (auto flag : flags)
		//{
		//	if (flag == FormatFlags::LONG)
		//	{
		//		isLong = true;
		//		break;
		//	}
		//}
		bool isLong = std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end();

		for (auto& res : m_contents) 
		{
			os << (res->type() == NodeType::DIR ? "D" : "F") << " | ";
			os.setf(std::ios::left);
			os.width(15);
			os << res->name();
			os.unsetf(std::ios::left);

			if (isLong)
			{
				os.setf(std::ios::right);
				std::string displaySize = std::to_string(res->size()) + " bytes";
				os << " | ";
				if (res->type() == NodeType::DIR)
				{
					os.width(2);
					os << res->count() << " | ";
				}
				else
					os << "   | ";
				os.width(10);
				os << displaySize << " | ";
				os.unsetf(std::ios::right);
			}
			else
				os << " |";
			os << std::endl;
		}
	}

}
