#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include "Reservation.h"

namespace seneca
{
	class Restaurant
	{
		Reservation** m_reservations;
		size_t m_size;
	};
}

#endif