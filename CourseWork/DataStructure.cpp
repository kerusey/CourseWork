#include "DataStructure.h"

#pragma warning (disable: 4996)

DataStructure::DataStructure(HEADER_E* generatedStructure) {
	this->entryPoint = generatedStructure;
}

size_t DataStructure::size() const {
	HEADER_E* cache = this->entryPoint;
	size_t counter = 0;
	for (; cache; cache = cache->pNext) { counter++; }
	return counter;
}

void DataStructure::printDataStructure() {
	HEADER_E* cache = this->entryPoint;
	size_t currentQueue = 1;

	for (; cache; cache = cache->pNext) {
		if (cache == nullptr) { continue; } // if there are null pointers in double linked list at first layer

		else {
			ITEM10** secondLayer = (ITEM10**)cache->ppItems;
			for (int counter = 0; counter < 26; counter++) {
				if (secondLayer[counter]) { ItemsHandler::printItemList((ITEM10*)(secondLayer[counter]), &currentQueue); }
				
			}
		}
	}
}

DataStructure::~DataStructure() {}