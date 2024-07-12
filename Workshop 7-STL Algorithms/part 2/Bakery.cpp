#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include "Bakery.h"


namespace seneca
{
	//a custom constructor that receives as a parameter the name of the file containing the information about the BakedGoods to be added to the collection.
	Bakery::Bakery(const std::string& filename)
	{
		std::ifstream file(filename);
		//If the filename is incorrect, this constructor should throw an exception.
		if (!file)
			throw std::runtime_error("Unable to open " + filename + ".");

		std::string line;
		while (std::getline(file, line)) {
			size_t lenBakeType = 8, lenDescription = 20, lenShelfLife = 14, lenStock = 8, lenPrice = 6, startPos{};
			//temporary object to hold the data
			BakedGood good;
			//read data into single BakedGood
			good.type = (removeSpace(line.substr(startPos, lenBakeType)) == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
			startPos += lenBakeType;
			good.description = removeSpace(line.substr(startPos, lenDescription));
			startPos += lenDescription;
			good.shelfLife = std::stoi(removeSpace(line.substr(startPos, lenShelfLife)));
			startPos += lenShelfLife;
			good.stock = std::stoi(removeSpace(line.substr(startPos, lenStock)));
			startPos += lenStock;
			good.price = std::stod(removeSpace(line.substr(startPos, lenPrice)));
			//The read in BakedGood will populate the collection.
			m_goods.push_back(good);
		}
	}


	//print the content of the collection into the parameter. Use the insertion operator
	//void Bakery::showGoods(std::ostream& os) const
	//{
	//	std::for_each(m_goods.begin(), m_goods.end(), [&](const BakedGood& bake)
	//		{
	//			os << bake;
	//		});
	//}

	std::string Bakery::removeSpace(const std::string& str)
	{
		if (!str.empty())
		{
			size_t first = str.find_first_not_of(' ');
			if (first == std::string::npos)
				return "";
			size_t last = str.find_last_not_of(' ');
			return str.substr(first, (last - first + 1));
		}
		return "";
	}

	//Helper function
	//inserts one BakedGood into the first parameter, using the following format (the width of each field is specified in brackets)
	std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
		out << std::left  << "* " << std::setw(10) << (b.type == BakedType::BREAD ? "Bread" : "Pastry")
			<< " * " << std::setw(20) << b.description
			<< " * " << std::setw(5) << b.shelfLife
			<< " * " << std::setw(5) << b.stock
			<< " * " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price
			<< " * ";

		return out;
	}

	//Part 2
	void Bakery::showGoods(std::ostream& os) const
	{
		auto totals = std::accumulate(m_goods.begin(), m_goods.end(), std::make_pair(0, 0.0),
			[&](std::pair<int, double> total, const BakedGood& good) 
			{
				os << good << std::endl;  
				return std::make_pair(total.first + good.stock, total.second + good.price);
			});

		os << "Total Stock: " << totals.first << std::endl;
		os << "Total Price: " << totals.second << std::endl;
	}

	//receives a parameter the name of the field used to sort the collection in ascending order.
	void Bakery::sortBakery(const std::string& field)
	{
		if (field == "Description") 
		{
			std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b) 
				{
					return a.description < b.description;
				});
		}
		else if (field == "Shelf") 
		{
			std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b) 
				{
					return a.shelfLife < b.shelfLife;
				});
		}
		else if (field == "Stock") 
		{
			std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b) 
				{
					return a.stock < b.stock;
				});
		}
		else if (field == "Price") {
			std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b) 
				{
					return a.price < b.price;
				});
		}
	}

	//receives a parameter of another Bakery object reference and combines the collection of BakedGoods from the current object and the parameter and returns the combined collection.
	std::vector<BakedGood> Bakery::combine(const Bakery& other)
	{
		// Sort before merge
		this->sortBakery("Price"); 
		const_cast<Bakery&>(other).sortBakery("Price");
		
		size_t size = this->m_goods.size() + other.m_goods.size();
		//std::vector<BakedGood> combined(size);
		std::vector<BakedGood> combined;
		combined.reserve(size);

		std::merge(this->m_goods.begin(), this->m_goods.end(),other.m_goods.begin(), other.m_goods.end(),
			std::back_inserter(combined),[](const BakedGood& a, const BakedGood& b) 
			{
				return a.price < b.price;  
			});

		return combined;
	}

	// receives the Description of a BakedGood and a BakedType as parameters, and returns true if the collection contains Stock of that BakedGood.
	bool Bakery::inStock(const std::string& description, BakedType type) const
	{
		return std::any_of(m_goods.begin(), m_goods.end(), [&description, type](const BakedGood& good) 
			{
				return good.description == description && good.type == type && good.stock > 0;
			});
	}

	//receives a BakedType as a parameter, and returns the list of all the out of stock items in the collection.
	std::list<BakedGood> Bakery::outOfStock(BakedType type) const
	{
		std::list<BakedGood> outStock;
		std::copy_if(m_goods.begin(), m_goods.end(), std::back_inserter(outStock), [=](const BakedGood& bake)
			{
				return bake.type == type && bake.stock == 0;
			});
		return outStock;
	}
}