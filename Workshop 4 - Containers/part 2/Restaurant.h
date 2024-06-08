#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include "Reservation.h"

namespace seneca
{
	class Restaurant
	{
		//This module should maintain a dynamically allocated array of pointers to objects of type Reservation
		Reservation** m_reservations {};
		size_t m_numReservation {}; //number of reservations
	public:
		Restaurant(){};
		//a constructor that receives as a parameter an array of pointers to objects of type Reservation
		Restaurant(const Reservation* reservations[], size_t cnt);

		//rule of 5
		Restaurant(const Restaurant&);
		Restaurant& operator=(const Restaurant&);
		Restaurant(Restaurant&&);
		Restaurant& operator=(Restaurant&&);
		~Restaurant();

		//a query that returns the number of reservations in the system.
		size_t size() const;
		//overload the insertion operator to insert the content of a Restaurant object into an ostream object.
		friend std::ostream& operator<<(std::ostream&, const Restaurant&);
	};
}

#endif