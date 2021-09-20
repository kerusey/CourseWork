#include <iostream> 
#include <iomanip>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
#include "DataStructure.h"

#pragma warning ( disable : 4996 )


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

	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;

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
	
	for (int i = 0; i < 5; i++) {
		try { structure->insertItem(insert[i]); }
		catch (int exception) { 
			switch (exception) {
				case 1: { std::cout << "Item ID already exists!" << std::endl; break; }
				case 2: { std::cout << "Format Error!" << std::endl; break; }
			}; 
		}
	} // TODO: rise exception if id already in dict

	structure->printDataStructure();
}

int main() {
	coursework1();
	return 0;
}