#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include "Reservation.h"

namespace seneca
{
	class ConfirmationSender
	{
		const Reservation** m_reservations;
		size_t m_size;
	};
}

#endif
