#include <iostream> 
#include <iomanip>
#include <vector>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
#include "DataStructure.h"

#pragma warning ( disable : 4996 )

void separator() {
	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
}

void coursework1() {
	DataStructure* structure = new DataStructure(GetStruct5(10, 20), 20);
	structure->printDataStructure();
	char insert[][5] = {
		"N M",
		"G Ah",
		"Fr B",
		"Ee S",
		"Th Z",
	};

	separator();

	for (int i = 0; i < 5; i++) {
		try { structure->insertItem(insert[i]); }
		catch (int exception) {
			switch (exception) {
			case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
			case 2: { std::cout << "Format Error!" << std::endl; break; }
			};
		}
	} // Append to structure from dict

	for (int i = 0; i < 2; i++) {
		try { structure->insertItem(); }
		catch (int exception) { 
			switch (exception) {
				case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
				case 2: { std::cout << "Format Error!" << std::endl; break; }
			}; 
		}
	} // Free append
	
	structure->printDataStructure(); // New data structure print

	for (int i = 0; i < 5; i++) {
		try { structure->insertItem(insert[i]); }
		catch (int exception) { 
			switch (exception) {
				case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
				case 2: { std::cout << "Format Error!" << std::endl; break; }
			}; 
		}
	} // Rised exception; id already in dict
	
	try { structure->insertItem((char*) "1234"); }
	catch (int exception) {
		switch (exception) {
		case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
		case 2: { std::cout << "Format Error!" << std::endl; break; }
		};
	} // Rised exception; error formatting

	separator();

	try { structure->removeItem((char*) "A Aame"); }
	catch (int exception) {
		switch (exception) {
		case 1: { std::cout << "No such thing in structure!" << std::endl; break; }
		case 2: { std::cout << "Format Error!" << std::endl; break; }
		};
	} // Rising "item missing" exception

	try { structure->removeItem(nullptr); }
	catch (int exception) {
		switch (exception) {
		case 1: { std::cout << "No such thing in structure!" << std::endl; break; }
		case 2: { std::cout << "Format Error!" << std::endl; break; }
		};
	} // Rising Format error

	for (int i = 0; i < 5; i++) {
		try { structure->removeItem(insert[i]); }
		catch (int exception) {
			switch (exception) {
			case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
			case 2: { std::cout << "Format Error!" << std::endl; break; }
			};
		}
	} // remoiving items, we previously added
	
	structure->printDataStructure();
	separator();
	structure->~DataStructure();
}

void coursework2() {
	/*
	DataStructure* structure = new DataStructure(GetStruct5(10, 20), 20);
	structure->printDataStructure();

	separator();

	ItemsHandler::printItem(structure->getItem((char*)"Fuchsia Rose"));

	separator();

	ITEM10* toBeAdded = (ITEM10*)GetItem(10);
	ItemsHandler::printItem(toBeAdded);

	separator();
	
	*structure += toBeAdded;
	structure->printDataStructure();

	separator();

	*structure -= (char*)"Fuchsia Rose";
	structure->printDataStructure();
	
	separator();
	*/


	DataStructure* structure = new DataStructure(GetStruct5(10, 20), 20);
	structure->printDataStructure();
	separator();
	std::cout << "New struct: " << std::endl;
	DataStructure anotherStructure;
	anotherStructure = *structure;
	// anotherStructure.printDataStructure();
	
	separator();

	// structure->~DataStructure();
	std::cout << "destructor check" << std::endl;
	//anotherStructure.printDataStructure();
	//structure->printDataStructure();
	/*
	separator();

	DataStructure* cache = new DataStructure(GetStruct5(10, 20), 20);
	structure->printDataStructure();
	separator();
	cache->printDataStructure();
	*/
}

void tests() {
	ITEM10* items = (ITEM10*) GetItem(10);
	items->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext->pNext->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext->pNext->pNext->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext->pNext->pNext->pNext->pNext = (ITEM10*)GetItem(10);
	items->pNext->pNext->pNext->pNext->pNext->pNext->pNext = (ITEM10*)GetItem(10);
	ItemsHandler::printItemList(items);
	separator();
	std::vector <ITEM10> collection = ItemsHandler::listToVector(items);
	
	DataStructure* structure = new DataStructure(GetStruct5(10, 10), 10);
	for (size_t i = 0; i < collection.size(); i++) {
		structure->insertItem(&collection[i]);
	}
	
	structure->printDataStructure();
	separator();
	
	std::vector <ITEM10> result = structure->getAllItems();
	for (auto i : result) { ItemsHandler::printItem(&i); }
}

int main() {
	tests();
	// coursework1(); // Done!
	// coursework2();
	return 0;
}