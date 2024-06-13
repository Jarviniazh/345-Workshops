#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

namespace seneca
{
	class Book
	{
		std::string m_authour{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{};
		double m_price{};
		std::string m_desc{};
	public:
		Book() {};
		Book(const std::string& strBook); //a constructor that receives a reference to an unmodifiable string that contains information about the book

		const std::string& title() const; // a query that returns the title of the book
		const std::string& country() const; // a query that returns the publication country
		const size_t& year() const; // a query that returns the publication year
		double& price(); // a function that returns the price by reference, allowing the client code to update the price
		std::string removeSpace(const std::string&); //removes the leading and trailing spaces from a string

		friend std::ostream& operator<<(std::ostream&, const Book&);
	};
}

#endif