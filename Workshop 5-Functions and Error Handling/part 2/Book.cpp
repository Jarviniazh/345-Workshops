#include <iostream>
#include <string>
#include "Book.h"

namespace seneca
{
	Book::Book(const std::string& strBook)
	{
		if(strBook.empty())
		{
			m_authour = "";
			m_title = "";
			m_country = "";
			m_price = 0.0;
			m_year = 0;
			m_desc = "";
			return;
		}

		size_t startPos = 0;
		size_t endPos = strBook.find(','); //comma after author
		m_authour = removeSpace(strBook.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = strBook.find(',', startPos); //comma after title
		m_title = removeSpace(strBook.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = strBook.find(',', startPos);
		m_country = removeSpace(strBook.substr(startPos, endPos - startPos));


		startPos = endPos + 1;
		endPos = strBook.find(',', startPos);
		m_price = std::stod(removeSpace(strBook.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = strBook.find(',', startPos);
		m_year = std::stoul(removeSpace(strBook.substr(startPos, endPos - startPos))); //std::stoul converts string to unsigned long

		startPos = endPos + 1;
		m_desc = removeSpace(strBook.substr(startPos));
	} 

	const std::string& Book::title() const
	{
		return m_title;
	}

	const std::string& Book::country() const
	{
		return m_country;
	}

	const size_t& Book::year() const
	{
		return m_year;
	}

	double& Book::price()
	{
		return m_price;
	}

	std::string Book::removeSpace(const std::string& str)
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

	std::ostream& operator<<(std::ostream& os, const Book& book)
	{
		if(!book.m_authour.empty() && !book.m_title.empty() && !book.m_country.empty() && !book.m_desc.empty() && book.m_year > 0)
		{
			os.width(20);
			os<<book.m_authour << " | ";

			os.width(22);
			os<< book.m_title << " | ";

			os.width(5);
			os << book.m_country << " | ";

			os.width(4);
			os << book.m_year << " | ";

			os.setf(std::ios::fixed);
			os.precision(2);
			os.width(6);
			os << book.m_price << " | ";
			os << book.m_desc << std::endl;
			os.unsetf(std::ios::fixed);
		}
		return os;
	}
}