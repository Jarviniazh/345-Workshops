#include <iostream>
#include <string>
#include "Movie.h"

namespace seneca
{
	Movie::Movie(const std::string& strMovie)
	{
		if(strMovie.empty())
		{
			m_title = "";
			m_year = 0;
			m_desc = "";
			return;
		}

		size_t startPos = 0;
		size_t endPos = strMovie.find(','); 
		m_title = removeSpace(strMovie.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = strMovie.find(',', startPos);
		m_year = std::stoul(removeSpace(strMovie.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		m_desc = removeSpace(strMovie.substr(startPos));
	}

	const std::string& Movie::title() const
	{
		return m_title;
	}

	std::string Movie::removeSpace(const std::string& str)
	{
		if(!str.empty())
		{
			size_t first = str.find_first_not_of(' '); 
			if (first == std::string::npos) 
				return "";
			size_t last = str.find_last_not_of(' '); 
			return str.substr(first, (last - first + 1));			
		}
		return "";
	}

	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		if(!movie.m_title.empty() && !movie.m_desc.empty() && movie.m_year > 0)
		{
			os.width(40);
			os << movie.m_title << " | ";
			os.width(4);
			os << movie.m_year << " | " << movie.m_desc << std::endl;
		}
		return os;
	}
}