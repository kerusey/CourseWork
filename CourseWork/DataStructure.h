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
	void printDataStructure();
	void insertItem(char* pNewItemID = 0);
	~DataStructure();

};
