#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Book.h"
#include "Book.h" // intentional

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	seneca::Book library[7];

	if (argc == 2) {
		// TODO: load the collection of books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the array "library"
		//       - lines that start with "#" are considered comments and should be ignored
		//       - if the file cannot be open, print a message to standard error console and
		//                exit from application with error code "AppErrors::CannotOpenFile"
		std::ifstream file(argv[1]);
		if (!file)
		{
			std::cerr << "AppErrors::CannotOpenFile\n";
			return 1;
		}

		std::string strBook;
		size_t index = 0; // 
		while (std::getline(file, strBook) && index < 7) //If not eof and index is less than 7
		{
			if (!strBook.empty() && strBook[0] != '#') // Check if the line is not a comment and not empty
			{
				library[index] = seneca::Book(strBook); 
				++index; 
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// TODO: create a lambda expression that fixes the price of a book accoding to the rules
	//       - the expression should receive a single parameter of type "Book&"
	//       - if the book was published in US, multiply the price with "usdToCadRate"
	//            and save the new price in the book object
	//       - if the book was published in UK between 1990 and 1999 (inclussive),
	//            multiply the price with "gbpToCadRate" and save the new price in the book object

	auto fixPrice = [&](seneca::Book& book)
	{
		if (book.country() == "US")
		{
			book.price() *= usdToCadRate;
		}
		else if(book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999)
		{
			book.price() *= gbpToCadRate;
		}
		return book.price();
	};


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
	for(auto i = 0u; i < 7u; ++i)
	{
		std::cout << library[i];
	}


	std::cout << "-----------------------------------------\n\n";

	// TODO: iterate over the library and update the price of each book
	//         using the lambda defined above.
	for (auto i = 0u; i < 7u; ++i)
	{
		library[i].price() = fixPrice(library[i]);
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
	for (auto i = 0u; i < 7u; ++i)
	{
		std::cout << library[i];
	}


	std::cout << "-----------------------------------------\n";

	return cout;
}