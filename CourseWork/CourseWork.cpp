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
	//structure->printDataStructure();
	char* trouble = (char*) "999479869";
	structure->insertItem(trouble);
	structure->insertItem(trouble);
	structure->insertItem(trouble);
	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
	structure->printDataStructure();
}

int main() {
	coursework1();
	return 0;
}