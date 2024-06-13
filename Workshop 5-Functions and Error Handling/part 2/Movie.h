#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

namespace seneca
{

	class Movie
	{
		std::string m_title{};
		size_t m_year{};
		std::string m_desc{};
	public:
		Movie(){};
		Movie(const std::string& strMovie); //receives the movie through a reference to a string.
		const std::string& title() const;  //a query that returns the title of the movie
		std::string removeSpace(const std::string&);

		friend std::ostream& operator<<(std::ostream&, const Movie&);

		template <typename T>
		void fixSpelling(T& spellChecker) //a templated function, passing to it the movie title and description.
		{
			spellChecker(m_title);
			spellChecker(m_desc);
		}
	};
}

#endif