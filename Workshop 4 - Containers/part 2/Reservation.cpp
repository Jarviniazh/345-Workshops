
#include <iostream>
#include <string>

#include "Reservation.h"

namespace seneca
{
	Reservation::Reservation(const std::string& res){
        size_t startPos = 0;
        size_t endPos = res.find(':'); //colon after id
        m_id = removeSpace(res.substr(startPos, endPos - startPos));

        startPos = endPos + 1;
        endPos = res.find(',', startPos); //comma after name
        m_name = removeSpace(res.substr(startPos, endPos - startPos));

        startPos = endPos + 1;
        endPos = res.find(',', startPos);
        m_email = removeSpace(res.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
        endPos = res.find(',', startPos);
        m_numParty = std::stoi(removeSpace(res.substr(startPos, endPos - startPos)));

        startPos = endPos + 1;
        endPos = res.find(',', startPos);
        m_day = std::stoi(removeSpace(res.substr(startPos, endPos - startPos)));

        startPos = endPos + 1;
        m_time = std::stoi(removeSpace(res.substr(startPos)));

    }

    //Function from StackOverflow: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
    std::string Reservation::removeSpace(const std::string& str)
    {
        size_t first = str.find_first_not_of(' '); // find index of first none space character, If str only contains spaces, find_first_not_of returns std::string::npos.
        if (first == std::string::npos) //If str only contains spaces, return empty string
            return "";
        size_t last = str.find_last_not_of(' '); // find index of last character that is not a space
        return str.substr(first, (last - first + 1));// return: a substring starting from first none space character to last none space character
    }



	void Reservation::update(int day, int time){
	    m_day = day;
	    m_time = time;
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& res){
        os << "Reservation ";

        os.setf(std::ios::right);
        os.width(10);
        os << res.m_id << ": ";
        os.width(20);
        os << res.m_name << "  ";

        os.unsetf(std::ios::right);
        os.setf(std::ios::left);
        os.width(20);
        os << "<" + res.m_email + ">";


        if(res.m_time >= 6 && res.m_time <=9){
        	os << "    Breakfast on day ";
		}
		else if(res.m_time >= 11 && res.m_time <= 15){
			os << "    Lunch on day ";
		}
		else if(res.m_time >= 17 && res.m_time <= 21){
			os << "    Dinner on day ";
		}
		else
		{
			os << "    Drinks on day ";
        }
        os << res.m_day << " @ " << res.m_time << ":00 for " << res.m_numParty;

		if(res.m_numParty == 1)
			os << " person.";
		else
		os<< " people.";

		os.unsetf(std::ios::left);
        os<<std::endl;
        return os;
	}

}

