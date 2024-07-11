#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <vector>
#include <list>

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
		//part 2
		size_t m_totalStock{}; //total stock of all items in the collection
		double m_totalPrice{}; //total price of all items in the collection
	public:
		Bakery() {};
		//a custom constructor that receives as a parameter the name of the file containing the information about the BakedGoods to be added to the collection.
		Bakery(const std::string&);
		//print the content of the collection into the parameter. Use the insertion operator
		void showGoods(std::ostream& os) const;

		//Helper function to remove leading and trailing spaces
		std::string removeSpace(const std::string&);

		//Part 2
		//receives a parameter the name of the field used to sort the collection in ascending order.
		void sortBakery();
		//receives a parameter of another Bakery object reference and combines the collection of BakedGoods from the current object and the parameter and returns the combined collection.
		std::vector<BakedGood> combine();
		// receives the Description of a BakedGood and a BakedType as parameters, and returns true if the collection contains Stock of that BakedGood.
		bool inStock() const;
		//receives a BakedType as a parameter, and returns the list of all the out of stock items in the collection.
		std::list<BakedGood> outOfStock() const;
	};

	//Helper function
	//inserts one BakedGood into the first parameter, using the following format (the width of each field is specified in brackets)
	std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}

#endif
