
#include <iostream>
#include <string>

//#include <algorithm> 
//#include <cctype>    

#include "Reservation.h"

namespace seneca
{
	Reservation::Reservation(const std::string& res){
        size_t startPos = 0;
        size_t endPos = res.find(':');
        m_id = removeSpace(res.substr(startPos, endPos - startPos));

        startPos = endPos + 1;
        endPos = res.find(',', startPos);
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

    //std::string Reservation::removeSpace(std::string str) {
    //    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    //    return str;
    //}

    std::string Reservation::removeSpace(const std::string& s) {
        size_t first = s.find_first_not_of(' ');
        size_t last = s.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos) // All spaces
            return "";
        return s.substr(first, (last - first + 1));
    }


	void Reservation::update(int day, int time){
	    m_day = day;
	    m_time = time;
	}

	std::ostream& operator<<(std::ostream& os, Reservation& res){
        os << "Reservation ";

        os.setf(std::ios::right);
        os.width(10);
        os << res.m_id << ":";
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

