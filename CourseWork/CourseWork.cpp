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

	structure = new DataStructure(GetStruct5(10, 20), 20);
	structure->printDataStructure();
	separator();
	std::cout << "New struct: " << std::endl;
	DataStructure anotherStructure;
	anotherStructure = *structure;
	anotherStructure.printDataStructure();
	
	separator();

	structure->~DataStructure();
	std::cout << "destructor check" << std::endl << std::endl;
	anotherStructure.printDataStructure();
	structure->printDataStructure();
	
	separator();

	anotherStructure.~DataStructure();
	structure->~DataStructure();

	structure = new DataStructure(GetStruct5(10, 20), 20);
	anotherStructure = *structure;
	
	std::cout << (*structure == anotherStructure) << std::endl;
	structure->insertItem((char*)"Game Over");
	structure->insertItem((char*)"Does It");
	std::cout << (*structure == anotherStructure) << std::endl;

	anotherStructure.insertItem((char*)"Does It");
	anotherStructure.insertItem((char*)"Game Over");

	std::cout << (*structure == anotherStructure) << std::endl; // Order matters!

	separator();

	structure->printDataStructure();
	structure->write((char*) "C:\\CourseWorkFolder\\dataset.dat");

	DataStructure* fromFile = new DataStructure((char*) "C:\\CourseWorkFolder\\dataset.dat");

	separator();

	fromFile->printDataStructure();

}

void tests() {
}

int main() {
	// tests();
	// coursework1(); // Done!
	coursework2();
	return 0;
}