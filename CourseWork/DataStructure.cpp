#include "DataStructure.h"

#pragma warning (disable: 4996)

DataStructure::DataStructure(HEADER_E* generatedStructure, size_t size): 
	entryPoint (generatedStructure), size(size) {}

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

void DataStructure::insertItem(char* pNewItemID) {
	size_t debug = 123;
	ITEM10* newItem = (ITEM10*) GetItem(10, ((char*) 999579869));
	ItemsHandler::printItem(newItem, &debug);

	newItem->pNext = (ITEM10*) this->entryPoint->ppItems[0];
	this->entryPoint->ppItems[0] = newItem;
	this->size++;

}

DataStructure::~DataStructure() {}