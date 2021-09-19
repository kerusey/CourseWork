#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"

class DataStructure {
	HEADER_E* entryPoint;
	
public:
	DataStructure(HEADER_E* generatedStructure);
	size_t size() const;
	void printDataStructure();
	~DataStructure();

};
