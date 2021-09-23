#pragma once
#include <iostream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream> 
#include <vector>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
#include "ItemsHandler.h"

class DataStructure {
	friend class boost::serialization::access;
	HEADER_E* entryPoint;
	size_t size;
	DataStructure* copyElements(DataStructure& original);
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& getAllItems();
	}
	
public:
	DataStructure(HEADER_E* generatedStructure, size_t size);
	DataStructure(); // CW2
	DataStructure(DataStructure& original); // CW2
	DataStructure(char* pFilename); // CW2
	void printDataStructure();
	void insertItem(char* pNewItemID = 0);
	void insertItem(ITEM10& item);
	bool isInStructure(char* itemID);
	void removeItem(char* itemID);
	ITEM10* getItem(char* pID); // CW2
	size_t getItemsNumber(); // CW2
	std::vector <ITEM10> getAllItems();

	// operators 
	void operator+=(ITEM10* anotherStructure); // Done
	void operator-=(char* pID); // Done
	DataStructure& operator=(DataStructure& right); // Done
	int operator==(DataStructure& other); // Done
	// operators 

	void write(char* pFilename);

	friend std::ostream& operator<<(std::ostream& out, DataStructure& list) {
		list.printDataStructure();
		return out;
	}

	~DataStructure();

};
