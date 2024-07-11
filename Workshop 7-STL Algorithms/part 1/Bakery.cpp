#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
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
	void Bakery::showGoods(std::ostream& os) const
	{
		std::for_each(m_goods.begin(), m_goods.end(), [&](const BakedGood& bake) {
			os << bake;
		});
	}

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
			<< " * " << '\n';

		return out;
	}
}