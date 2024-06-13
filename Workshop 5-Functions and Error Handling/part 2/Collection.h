#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>

namespace seneca
{
	template <typename T>
	class Collection
	{
		T* m_items {};
		std::string m_name {};
		size_t m_size{};
		void (*m_observer)(const Collection<T>&, const T&){};
	public:
		Collection(const std::string& name) : m_items{nullptr}, m_name{name}, m_size{0}, m_observer{nullptr} {};

		Collection(const Collection& other) = delete;
		Collection& operator=(const Collection& other) = delete;

		~Collection()
		{
			delete[] m_items;
		}

		const std::string& name() const
		{
			return m_name;
		}

		size_t size() const
		{
			return m_size;
		}

		void setObserver(void (*observer)(const Collection<T>&, const T&))
		{
			m_observer = observer;
		}


		Collection<T>& operator+=(const T& item)
		{
			for(auto i = 0u; i< m_size; ++i)
			{
				if(m_items[i].title() == item.title())
				{
					return *this;
				}
			}

			T* temp = new T[m_size + 1];
			for (auto i = 0u; i < m_size; ++i)
			{
				temp[i] = m_items[i];
			}
			temp[m_size] = item;
			
			delete[] m_items;
			m_items = temp;
			m_size++;

			if(m_observer != nullptr)
			{
				m_observer(*this, item);
			}
			return *this;
		}

		T& operator[](size_t idx) const
		{ 
			if (idx >= m_size) 
			{
				throw std::out_of_range("** EXCEPTION: Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
			}
			return m_items[idx];
		}

		T* operator[](const std::string& title) const
		{
			for(auto i = 0u; i < m_size; ++i)
			{
				if(m_items[i].title() == title)
				{
					return &m_items[i];
				}
			}
			return nullptr;
		}

		friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection)
		{
			for(auto i = 0u; i < collection.size(); ++i)
			{
				os << collection[i];
			}
			return os;
		}
	};
}

#endif
