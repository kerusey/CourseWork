#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
#include "ItemsHandler.h"

class DataStructure {
	HEADER_E* entryPoint;
	size_t size;
	
public:
	DataStructure(HEADER_E* generatedStructure, size_t size);
	DataStructure(); // CW2
	DataStructure(char* pFilename); // CW2
	void printDataStructure();
	void insertItem(char* pNewItemID = 0);
	bool isInStructure(char* itemID);
	void removeItem(char* itemID);
	ITEM10* getItem(char* pID); // CW2
	size_t getItemsNumber(); // CW2

	// operators 
	void operator+=(ITEM10* anotherStructure); // Done
	void operator-=(char* pID); // Done
	DataStructure* operator=(DataStructure* right); 
	int operator==(DataStructure& other); 
	// operators 

	friend std::ostream& operator<<(std::ostream& out, DataStructure& list) {
		list.printDataStructure();
		return out;
	}

	~DataStructure();

};
