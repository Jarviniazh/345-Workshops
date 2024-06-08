#include <iostream>
#include "ConfirmationSender.h"

namespace seneca
{
	ConfirmationSender::ConfirmationSender(const ConfirmationSender& source)
	{
		*this = source;
	}

	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& source) {
		if (this != &source) {
			delete[] m_pReservations;
			m_numReservation = source.m_numReservation;

			//Check the source is not empty, then copy the data
			if(source.m_pReservations != nullptr){
				m_pReservations = new const Reservation* [m_numReservation];
				for (size_t i = 0; i < m_numReservation; ++i)
					m_pReservations[i] = source.m_pReservations[i]; //only copy the address
			}
			else{
				m_pReservations = nullptr;
			}
		}
		return *this;
	}
	//move constructor
	ConfirmationSender::ConfirmationSender(ConfirmationSender&& source)
	{
		*this = std::move(source);
	}
	//move assignment operator
	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& source)
	{
		if(this != &source){
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
		//if the address of res is already in the array, this operator does nothing
		for(size_t i = 0; i < m_numReservation; ++i){
			if (m_pReservations[i] == &res)
				return *this;
		}

		//resizes the array to make room for res if necessary
		const Reservation** temp = new const Reservation * [m_numReservation + 1];

		//stores the address of res in the new array
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
		//find the index of the res if it exists
		for (size_t i = 0; i < m_numReservation; ++i){
			if (m_pReservations[i] == &res){
				resIndex = i;
				break;
			}
		}

		//Resizes the array to remove the res if it exists
		if(resIndex != m_numReservation){
			for (size_t i = resIndex ; i < m_numReservation - 1; ++i)
				m_pReservations[i] = m_pReservations[i + 1];
			m_numReservation--;
		}
		return *this;
	}


	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& confirmation)
	{
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send" << std::endl;
		os << "--------------------------" << std::endl;

		//if there are no reservation to confirm
		if (confirmation.m_numReservation == 0){
			os << "There are no confirmations to send!" << std::endl;
			os << "--------------------------" << std::endl;
		}
		else{
			for (size_t i = 0; i < confirmation.m_numReservation; i++)
				os << *confirmation.m_pReservations[i];
			os << "--------------------------" << std::endl;
		}

		return os;
	}
}
