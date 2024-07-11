#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <vector>

namespace seneca
{
	enum class BakedType {
		BREAD, PASTERY
	};

	struct BakedGood
	{
		BakedType type{}; //Baked Type (either BREAD or PASTERY from the above enum)
		std::string description{}; //Description of the baked item
		size_t shelfLife{}; //Shelf life of the baked item
		size_t stock{}; //The amount of stock for the item
		double price{}; //The price of the item
	};

	class Bakery
	{
		std::vector<BakedGood> m_goods{}; //manages a collection of objects of type BakedGood
	public:
		Bakery() {};
		//a custom constructor that receives as a parameter the name of the file containing the information about the BakedGoods to be added to the collection.
		Bakery(const std::string&);
		//print the content of the collection into the parameter. Use the insertion operator
		void showGoods(std::ostream& os) const;

		std::string removeSpace(const std::string&);
	};

	//Helper function
	//inserts one BakedGood into the first parameter, using the following format (the width of each field is specified in brackets)
	std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}

#endif
