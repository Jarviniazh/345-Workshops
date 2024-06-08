#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include "Reservation.h"

namespace seneca
{
	class Restaurant
	{
		Reservation** m_reservations {};
		size_t m_numReservation {};
	public:
		Restaurant(const Reservation* reservations[], size_t cnt);
		Restaurant(const Restaurant&);
		Restaurant& operator=(const Restaurant&);
		Restaurant(Restaurant&&);
		Restaurant& operator=(Restaurant&&);

		~Restaurant();

		size_t size() const;
		friend std::ostream& operator<<(std::ostream&, const Restaurant&);
	};
}

#endif