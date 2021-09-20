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
			ITEM10** secondLayer = (ITEM10**) cache->ppItems;
			for (int counter = 0; counter < 26; counter++) {
				if (secondLayer[counter]) { ItemsHandler::printItemList((ITEM10*)(secondLayer[counter]), &currentQueue); }	
			}
		}
	}
}

bool DataStructure::isInStructure(char* itemID) {
	HEADER_E* cache = this->entryPoint;

	for (; cache; cache = cache->pNext) {
		if (cache == nullptr) { continue; } // if there are null pointers in double linked list at first layer
		else {
			ITEM10** secondLayer = (ITEM10**) cache->ppItems;
			for (int counter = 0; counter < 26; counter++) {
				if (secondLayer[counter]) {
					if (ItemsHandler::isInList(secondLayer[counter], itemID)) { return true; }
				}
			}
		}
	}
	return false;
}

void DataStructure::insertItem(char* pNewItemID) {
	if (isInStructure(pNewItemID)) {
		throw 1;
	}

	if (pNewItemID == 0 || ItemsHandler::validateIDFormat(pNewItemID)) {
		ITEM10* newItem = (ITEM10*)GetItem(10, ((char*)pNewItemID));

		newItem->pNext = (ITEM10*)this->entryPoint->ppItems[0];
		this->entryPoint->ppItems[0] = newItem;
		this->size++;
	}

	else {
		throw 2;
	}
}

DataStructure::~DataStructure() {}