#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <exception>

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

		//this class doesn't support any copy operations; delete all of them.
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
			//If item is already in the collection, this function does nothing.
			for(auto i = 0u; i< m_size; ++i)
			{
				if(m_items[i].title() == item.title())
				{
					return *this;
				}
			}
			//resizes the array of items to accommodate the new item
			T* temp = new T[m_size + 1];
			for (auto i = 0u; i < m_size; ++i)
			{
				temp[i] = m_items[i];
			}
			temp[m_size] = item;
			
			delete[] m_items;
			m_items = temp;
			m_size++;

			//if an observer has been registered, this operator calls the observer function passing the current object (*this) and the new item as arguments.
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
				std::string msg = "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.";
				throw std::out_of_range(msg);
			}
			return m_items[idx];
		}

		T* operator[](const std::string& title) const
		{
			if (!title.empty())
			{
				for (auto i = 0u; i < m_size; ++i)
				{
					if (m_items[i].title() == title)
					{
						return &m_items[i];
					}
				}
			}
			return nullptr;
		}

		friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection)
		{
			if(collection.m_size > 0)
			{
				for(auto i = 0u; i < collection.m_size; ++i)
					os << collection[i];
			}
			
			return os;
		}
	};
}

#endif
