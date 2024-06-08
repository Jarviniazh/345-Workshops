#include <iostream>
#include "ConfirmationSender.h"

namespace seneca
{
	ConfirmationSender::ConfirmationSender(const ConfirmationSender& source)
	{
		*this = source;
	}

	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
		if (this != &other) {
			const Reservation** newReservations = nullptr;
			if (other.m_numReservation > 0) {
				newReservations = new const Reservation * [other.m_numReservation];
				for (size_t i = 0; i < other.m_numReservation; ++i) {
					newReservations[i] = other.m_pReservations[i]; 
				}
			}

			delete[] m_pReservations;  

			m_pReservations = newReservations;
			m_numReservation = other.m_numReservation;
		}
		return *this;
	}

	ConfirmationSender::ConfirmationSender(ConfirmationSender&& source)
	{
		*this = std::move(source);
	}
	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& source)
	{
		if(this != &source)
		{
			delete[] m_pReservations;
			m_pReservations = source.m_pReservations;
			source.m_pReservations = nullptr;

			m_numReservation = source.m_numReservation;
			source.m_numReservation = 0;
		}
		return *this;
	}

	ConfirmationSender::~ConfirmationSender()
	{
		delete [] m_pReservations;
	}

	ConfirmationSender& ConfirmationSender:: operator+=(const Reservation& res)
	{
		for(size_t i = 0; i < m_numReservation; ++i)
		{
			if (m_pReservations[i] == &res)
				return *this;
		}

		const Reservation** temp = new const Reservation * [m_numReservation + 1];

		for(size_t i = 0; i < m_numReservation; ++i)
			temp[i] = m_pReservations[i];

		temp[m_numReservation] = &res;
		m_numReservation++;

		delete [] m_pReservations;
		m_pReservations = temp;
		return *this;
	}

	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
	{
		size_t resIndex = m_numReservation;
		for (size_t i = 0; i < m_numReservation; ++i)
		{
			if (m_pReservations[i] == &res){
				resIndex = i;
				break;
			}
		}

		if(resIndex != m_numReservation){
			
			for (size_t i = resIndex ; i < m_numReservation - 1; ++i)
			m_pReservations[i] = m_pReservations[i + 1];
			m_numReservation--;
		}
		//m_numReservation--;

		//

		//delete[] m_pReservations;
		//m_pReservations = temp;
		return *this;
	}


	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& confirmation)
	{
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send" << std::endl;
		os << "--------------------------" << std::endl;

		if (confirmation.m_numReservation == 0)
		{
			os << "There are no confirmations to send!" << std::endl;
			os << "--------------------------" << std::endl;
		}
		else
		{
			for (size_t i = 0; i < confirmation.m_numReservation; i++)
				os << *confirmation.m_pReservations[i];
			os << "--------------------------" << std::endl;
		}


		return os;
	}
}
