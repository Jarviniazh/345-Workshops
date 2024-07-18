#include <algorithm>
#include <iostream>

#include <fstream>
#include <string>
#include "Database.h"


namespace seneca
{
	std::shared_ptr<Database> Database::m_db{};

	Database::Database(const std::string& filename) : m_filename(filename)  //a private constructor to prevent client from instantiating this class.
	{
		//prints to the screen the address of the current instance and the prototype of the constructor
		std::cout << std::hex;
		std::cout << "[" << this << "]" << " Database(const std::string&)" << std::endl;
		//opens the file and read the key/value pairs into the attributes
		std::ifstream file(filename);

		std::string key{}, value{}, line{};

		while(m_numEntries < 20 &&std::getline(file, line))
		{
			size_t pos = line.find("$");
			key = removeSpace(line.substr(0, pos));
			value = line.substr(pos);
			//find _ for key
			size_t underlinePos = key.find("_");
			if(underlinePos != std::string::npos)
				key[underlinePos] = ' '; //replace _ with space

			m_keys[m_numEntries] = key;
			m_values[m_numEntries++] = value;
		}
		file.close();
	}

	std::string Database::removeSpace(const std::string& str) 
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


	std::shared_ptr<Database> Database::getInstance(const std::string& filename)
	{
		//if the class Database has not been instantiated  then this function creates an instance of type Database (using the private constructor) and stores it in the static attribute. 
		if (m_db.use_count() == 0)
		{
			m_db = std::shared_ptr<Database>(new Database(filename));
		}
		return m_db;
	}

	Err_Status Database::GetValue(const std::string& key, std::string& value) const  //a query that searches in the array of keys for a the first parameter
	{
		//if the key is found, store in the second parameter the corresponding value from the array of values and return Err_Status::Err_Success
		auto found = std::find(std::begin(m_keys), std::end(m_keys), key);
		if (found != std::end(m_keys)) {
			size_t index = std::distance(std::begin(m_keys), found);
			value = m_values[index];
			return Err_Status::Err_Success;
		}

		//if the key is not found, return Err_Status::Err_NotFound
		return Err_Status::Err_NotFound;
	}

	Err_Status Database::SetValue(const std::string& key, const std::string& value) //a modifier that receives as parameters a key and a value.
	{
		if(m_numEntries < 20)
		{
			//If there is space in the database(the capacity of the array not been reached), the key / value pair is added and the function returns Err_Success
			m_keys[++m_numEntries] = key;
			m_values[++m_numEntries] = value;;
			return Err_Status::Err_Success;
		}
		return Err_Status::Err_OutOfMemory;
	}

	Database::~Database() //destructor
	{
		std::cout << std::hex;
		std::cout << "[" << this << "]" << " ~Database()" << std::endl;

		std::string backup = m_filename + ".bkp.txt";
		std::ofstream file(backup);

		size_t index{}; 
		for (const auto& key : m_keys) 
		{
			if (index <  m_numEntries) 
			{ 
				file << key << " -> " << m_values[index++] << std::endl;
			}
		}
		file.close();
	}
}