#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include "Reservation.h"

namespace seneca
{
	class ConfirmationSender
	{
		//This module should maintain a dynamically allocated array of pointers to objects of type Reservation
		const Reservation** m_pReservations{}; //
		size_t m_numReservation{}; //number of reservations
	public:
		ConfirmationSender() {};
		//rule of 5
		ConfirmationSender(const ConfirmationSender&);
		ConfirmationSender& operator=(const ConfirmationSender&);
		ConfirmationSender(ConfirmationSender&&);
		ConfirmationSender& operator=(ConfirmationSender&&);
		~ConfirmationSender();

		//adds the reservation res to the array by adding its address.
		ConfirmationSender& operator+=(const Reservation& res);
		//removes the reservation res from the array by removing its address
		ConfirmationSender& operator-=(const Reservation& res);
		//overload the insertion operator to insert the content of a ConfirmationSender object into an ostream object:
		friend std::ostream& operator<<(std::ostream&, const ConfirmationSender&);

	};
}

#endif
