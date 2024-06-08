#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

namespace seneca
{
	class Reservation {
	    //reservation id: an array of characters
	    std::string m_id {};
	    //the name on the reservation
	    std::string m_name {};
	    //the email to be used to send a confirmation that the reservation can be honored or cannot
	    std::string m_email{};
	    //the number of people in the party
	    int m_numParty {};
	    //the day when the party expects to come (for simplicity, the day is an integer between 1 and 28)
	    int m_day {};
	    //the hour when the party expects to come (for simplicity, the hour is an integer between 1 and 24)
	    int m_time {};

	public:
	    Reservation(){};
	    Reservation(const std::string&);

		//a modifier that receives as parameters a new day and time for the reservation and updates the attributes with received values.
	    void update(int day, int time);

		//remove leading and trailing spaces from a string
		std::string removeSpace(const std::string& s);

		//overload the insertion operator to insert the contents of a reservation object into an ostream object
	    friend std::ostream& operator<<(std::ostream&, const Reservation&);

		//Part 2
		//default rule of 5
		Reservation(const Reservation& source)=default;
		Reservation& operator=(const Reservation& source) = default;
		Reservation(Reservation&& source) = default;
		Reservation& operator=(Reservation&& source) = default;
		~Reservation() = default;
	};


}


#endif
