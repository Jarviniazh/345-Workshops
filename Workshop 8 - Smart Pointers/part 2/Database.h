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

	template<typename T>
	class Database
	{
		static std::shared_ptr<Database> m_db; //store the address of the one and only instance of type Database
		size_t m_numEntries{}; //A variable representing the number of entries in the database.
		std::string m_keys[20]{};//A statically - allocated array of strings representing the keys.The size of this array is 20.
		T m_values[20]{};//A statically - allocated array of strings representing the values.The size of this array is 20.
		std::string m_filename{};//A string representing the database file name.

		Database(const std::string& filename) : m_filename(filename) //a private constructor to prevent client from instantiating this class.
		{
			//prints to the screen the address of the current instance and the prototype of the constructor
			std::cout << std::hex;
			std::cout << "[" << this << "]" << " Database(const std::string&)" << std::dec<< std::endl;
			//opens the file and read the key/value pairs into the attributes
			std::ifstream file(filename);

			std::string key{}, valueStr{}, line{};
			T value{};

			while (m_numEntries < 20 && std::getline(file, line))
			{
				size_t pos = line.find(" ");
				key = line.substr(0, pos);
				pos = line.rfind(" ");
				valueStr = line.substr(pos + 1);

				//find _ for key
				size_t underlinePos = key.find("_");
				if (underlinePos != std::string::npos)
					key[underlinePos] = ' '; //replace _ with space

				//std::cout << key << "        orignal: " << valueStr << std::endl;
				std::istringstream(valueStr) >> value;


				encryptDecrypt(value);
				//std::cout << key << "        encrpty: " << value << std::endl;
				m_keys[m_numEntries] = key;
				m_values[m_numEntries++] = value;
			}
			file.close();
		}

		//Part 2
		void encryptDecrypt(T& value) {}; // an empty body function(does nothing, we will specialize it later).


	public:
		static std::shared_ptr<Database<T>> getInstance(const std::string& filename)
		{
			if (!m_db) {
				m_db = std::shared_ptr<Database<T>>(new Database<T>(filename)); // Directly use new with std::shared_ptr
			}
			return m_db;
		}

		Err_Status GetValue(const std::string& key, T& value) const  //a query that searches in the array of keys for a the first parameter
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

		Err_Status SetValue(const std::string& key, const T& value) //a modifier that receives as parameters a key and a value.
		{
			if (m_numEntries < 20)
			{
				//If there is space in the database(the capacity of the array not been reached), the key / value pair is added and the function returns Err_Success
				m_keys[++m_numEntries] = key;
				m_values[m_numEntries] = value;
				return Err_Status::Err_Success;
			}
			return Err_Status::Err_OutOfMemory;
		}

		~Database() //destructor
		{
			std::cout << std::hex;
			std::cout << "[" << this << "]" << " ~Database()" << std::dec << std::endl;

			std::string backup = m_filename + ".bkp.txt";
			std::ofstream file(backup);
			size_t index{};
			for (const auto& key : m_keys)
			{
				encryptDecrypt(m_values[index]);
				file << key << " -> " << m_values[index] << std::endl;
			}
			file.close();
		}

	};

	template<typename T>
	std::shared_ptr<Database<T>> Database<T>::m_db{};

	//template<typename T>
	//std::shared_ptr<Database<T>> getInstance(const std::string& filename)
	//{
	//	//if the class Database has not been instantiated  then this function creates an instance of type Database (using the private constructor) and stores it in the static attribute. 
	//	if (Database<T>::m_db.use_count() == 0)
	//	{
	//		Database<T>::m_db = std::shared_ptr<Database<T>>(new Database<T>(filename));
	//	}
	//	return Database<T>::m_db;
	//}

	//Specialization
	//specialize the encryptDecrypt() for the type std::string as following(pseudocode)
	template<>
	void Database<std::string>::encryptDecrypt(std::string& value)
	{
		const char secret[]{ "secret encryption key" };

		/*foreach character C in the parameter
			foreach character K in the secret
			C = C ^ K*/
		for (auto& c : value) {
			for (size_t j = 0; j < sizeof(secret) - 1; ++j) { 
				c = c ^ secret[j];
			}
		}

	}
	//specialize the encryptDecrypt() for the type long long as following(pseudocode)
	template<>
	void Database<long long>::encryptDecrypt(long long& value)
	{
		const char secret[]{ "super secret encryption key" };
		
	/*	foreach byte B in the parameter
			foreach character K in the secret
			B = B ^ K*/
		char* bytePtr = reinterpret_cast<char*>(&value);
		size_t numBytes = sizeof(long long);
		size_t secretLength = sizeof(secret) - 1;

		// Encrypting process
		for (size_t i = 0; i < numBytes; ++i) {
			for (size_t j = 0; j < secretLength; ++j) {
				bytePtr[i] = bytePtr[i] ^ secret[j];
			}
		}

		// Directly showing the change in long long
		//std::cout << "Encrypted value in long long: " << value << std::endl;
		//std::cout << "Encrypted value in hex: " << std::hex << value << std::dec << std::endl;
	}

}

#endif

