#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H
#include <memory>
namespace seneca
{
	enum class Err_Status
	{
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory,
	};

	class Database
	{
		static std::shared_ptr<Database> m_db; //store the address of the one and only instance of type Database
		size_t m_numEntries{}; //A variable representing the number of entries in the database.
		std::string m_keys[20]{};//A statically - allocated array of strings representing the keys.The size of this array is 20.
		std::string m_values[20]{};//A statically - allocated array of strings representing the values.The size of this array is 20.
		std::string m_filename{};//A string representing the database file name.

		Database(const std::string& filename);  //a private constructor to prevent client from instantiating this class.

	public:
		static std::shared_ptr<Database> getInstance(const std::string& filename);

		Err_Status GetValue(const std::string& key, std::string& value) const;  //a query that searches in the array of keys for a the first parameter
		Err_Status SetValue(const std::string& key, const std::string& value); //a modifier that receives as parameters a key and a value.

		~Database(); //destructor

		std::string removeSpace(const std::string& str);
	};
}

#endif

