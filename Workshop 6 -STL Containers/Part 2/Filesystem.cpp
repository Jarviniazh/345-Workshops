#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Filesystem.h"
#include "File.h"

namespace seneca
{
	Filesystem::Filesystem(const std::string& filename, const std::string& root)
	{
		//This member first creates a dynamically allocated Directory object to set as the root directory and the current working directory.
		m_root = new Directory(root);
		m_current = m_root;
		//Then loads the content of the file
		std::ifstream file(filename);
		if (!file) {
			throw std::runtime_error("Bad file name!");
		}

		//each line in the file represents a resource in the filesystem that you must create using the appropriate class (File or Directory)
		std::string line;
		while (std::getline(file, line)) {
			line = removeSpace(line);

			size_t pipePos = line.find('|');

			std::string filePath{}, fileContents{};
			if(pipePos != std::string::npos)
			{
				filePath = removeSpace(line.substr(0, pipePos)); //file path
				fileContents = removeSpace(line.substr(pipePos + 1)); //file contents
			}
			else //directory path
				filePath = line;

			//For each line, the constructor dynamically creates a new Directory for each component of the path
			Directory* currentDir = m_current;  

			std::vector<std::string> pathParts; // Store the parts of the path
			size_t startPos = 0;
			size_t found = filePath.find('/');
			//Separate the path by /
			while (found != std::string::npos)
			{ 
				if (found > startPos) //if there is a directory in the path
					pathParts.push_back(filePath.substr(startPos, found - startPos) + "/");  // Add the directory to the pathParts
				startPos = found + 1;
				found = filePath.find('/', startPos);
			}
			if (startPos < filePath.size()) //add the last part of the path
				pathParts.push_back(filePath.substr(startPos));  
			

			for (auto i = 0u; i < pathParts.size(); ++i)
			{
				if (i == pathParts.size() - 1 && !fileContents.empty()) //file without a directory
				{ 
					//create file and add it to the current directory
					File* newFile = new File(pathParts[i], fileContents);
					*currentDir += newFile;
				}
				else // directory path
				{
					//check if the directory already exists
					Resource* found = currentDir->find(pathParts[i]);
					if (!found) //if the directory does not exist, create it
					{
						Directory* newDir = new Directory(pathParts[i]);
						*currentDir += newDir; //add the new directory to the current directory
						currentDir = newDir; //update the absolute location 
					}
					else //already exists on the root directory, do not create a new one
					{
						currentDir = dynamic_cast<Directory*>(found);
					}
				}
			}
		}
		file.close();
	}

	std::string Filesystem::removeSpace(const std::string& str)
	{
		if (!str.empty())
		{
			size_t first = str.find_first_not_of(' ');
			if (first == std::string::npos)
				return "";
			size_t last = str.find_last_not_of(' ');
			return str.substr(first, (last - first + 1));
		}
		return "";
	}

	//Move operations
	Filesystem::Filesystem(Filesystem&& source)
	{
		*this = std::move(source);
	}

	Filesystem& Filesystem::operator=(Filesystem&& source)
	{
		if(this != &source)
		{
			delete m_root;
			m_root = source.m_root;
			source.m_root = nullptr;

			delete m_current;
			m_current = source.m_current;
			source.m_current = nullptr;
		}
		return *this;
	}

	//adds a resource to the current directory.
	Filesystem& Filesystem::operator+=(Resource* res)
	{
		*m_current += res;
		return *this;
	}

	//changes the current directory to the directory(located in the current directory) whose name matches argument.
	Directory* Filesystem::change_directory(const std::string& dirname)
	{
		//if an empty string is passed, change the current directory to the root directory.
		if (dirname.empty())
			m_current = m_root; 
		else 
		{
			//Check if the directory exists in the current directory
			Resource* found = m_current->find(dirname);
			if (found && found->type() == NodeType::DIR) 
				m_current = dynamic_cast<Directory*>(found);
			else //if no directory with the specified name exists, report an std::invalid_argument exception with the message
				throw std::invalid_argument("Cannot change directory! " + dirname + " not found!");
		}
		return m_current;
	}

	//a query that returns the current directory.
	Directory* Filesystem::get_current_directory() const
	{
		return m_current;
	}

	//Destructor
	Filesystem::~Filesystem()
	{
		delete m_root;
		//delete m_current;
	}
}
