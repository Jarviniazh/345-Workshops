#include <iostream>
#include "Restaurant.h"

namespace seneca
{
	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt)
	{
		m_numReservation = cnt;
		m_reservations = new Reservation * [m_numReservation];
		for (size_t i = 0; i < m_numReservation; ++i) {
			m_reservations[i] = new Reservation(*reservations[i]);
		}
	}
	Restaurant::Restaurant(const Restaurant& source)
	{
		*this = source;
	}

	Restaurant& Restaurant::operator=(const Restaurant& source)
	{
        if (this != &source) {
            Reservation** newReservations = nullptr;
            if (source.m_numReservation > 0) {
                newReservations = new Reservation * [source.m_numReservation];
                for (size_t i = 0; i < source.m_numReservation; ++i) {
                    newReservations[i] = new Reservation(*source.m_reservations[i]);
                }
            }

            for (size_t i = 0; i < m_numReservation; ++i) {
                delete m_reservations[i];
            }
            delete[] m_reservations;

            m_reservations = newReservations;
            m_numReservation = source.m_numReservation;
        }
        return *this;
	}
	Restaurant::Restaurant(Restaurant&& source)
	{
		*this = std::move(source);
	}
	Restaurant& Restaurant::operator=(Restaurant&& source)
	{
		if(this != &source)
		{
			delete[] m_reservations;
			m_reservations = source.m_reservations;
			source.m_reservations = nullptr;

			m_numReservation = source.m_numReservation;
			source.m_numReservation = 0;
		}
		return *this;
	}




	Restaurant::~Restaurant()
	{
		for(size_t i = 0; i < m_numReservation; i++)
			delete m_reservations[i];
		delete [] m_reservations;
	}

	size_t Restaurant::size() const
	{
		return m_numReservation;
	}
	std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant)
	{
		static size_t CALL_CNT = 0;
		CALL_CNT++;
		os << "--------------------------" << std::endl;
		os << "Fancy Restaurant (" << CALL_CNT << ")" << std::endl;
		os << "--------------------------" << std::endl;

		if(restaurant.m_numReservation == 0)
		{
			os << "This restaurant is empty!" << std::endl;
			os << "--------------------------" << std::endl;
		}
		else
		{
			for(size_t i = 0; i < restaurant.m_numReservation; i++)
				os << *restaurant.m_reservations[i];
			os << "--------------------------" << std::endl;
		}

		return os;
	}
}
