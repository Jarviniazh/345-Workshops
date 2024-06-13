#include <iostream>
#include "Movie.h"

namespace seneca
{
	Movie::Movie(const std::string& strMovie)
	{
		
	}

	const std::string& Movie::title() const
	{
		return m_title;
	}

	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		if(!movie.m_title.empty())
		{
			os.width(40);
			os << movie.m_title << " | ";
			os.width(4);
			os << movie.m_year << " | " << movie.m_desc << std::endl;

		}
		return os;
	}
}