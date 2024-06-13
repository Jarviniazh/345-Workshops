#include <iostream>
#include <string>
#include <fstream>
//#include <sstream> 
#include "SpellChecker.h"

namespace seneca
{
	SpellChecker::SpellChecker(const char* filename)
	{
		std::ifstream file(filename);
		if(!file)
		{
			throw "Bad file name!";
		}
		else
		{
			std::string line;
			size_t index = 0;
			//load the bad words and good words from the file
			//while(std::getline(file, line) && index < 6)
			//{
			//	std::stringstream ss(line);
			//	ss >> m_badWords[index];
			//	ss >> m_goodWords[index];
			//	++index;
			//}
			//other way to read file: cin >> str1 >> str2;
	
			while (index < 6 && file >> m_badWords[index] >> m_goodWords[index])
				++index;
		}
		file.close();
	}

	void SpellChecker::operator()(std::string& text) //https://www.geeksforgeeks.org/find-and-replace-all-occurrences-of-a-substring-in-string-in-cpp/
	{
		if(!text.empty())
		{
			for (size_t i = 0; i < 6; ++i) 
			{
				size_t pos = text.find(m_badWords[i]);
				while (pos != std::string::npos) 
				{
					//debug
					//std::cout << "Replacing: " << m_badWords[i] << " at position: " << pos << std::endl;
					text.replace(pos, m_badWords[i].size(), m_goodWords[i]);
					m_numReplace[i]++; //increment the number of replacements
					//debug
					//std::cout << "--------Replaced Bad word [" << m_badWords[i] << "] with num " << m_numReplace[i] << std::endl;
					pos = text.find(m_badWords[i], pos + m_goodWords[i].size());
				}
			}
		}

	}

	void SpellChecker::showStatistics(std::ostream& out) const
	{
		out << "Spellchecker Statistics\n";
		for (auto i = 0u; i < 6; ++i)
		{
			out.width(15);
			out.setf(std::ios::right);
			out << m_badWords[i] << ": " << m_numReplace[i] << " replacements\n";
			out.unsetf(std::ios::right);
		}
	}
}