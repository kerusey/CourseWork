#include "DataStructure.h"

#pragma warning (disable: 4996)

DataStructure::DataStructure(HEADER_E* generatedStructure, size_t size): 
	entryPoint (generatedStructure), size(size) {}

DataStructure::DataStructure() :
	entryPoint(nullptr), size(0) {}

DataStructure::DataStructure(char* pFilename) {
	
}

size_t DataStructure::getItemsNumber() { return this->size; }

ITEM10* DataStructure::getItem(char* itemID) {
	HEADER_E* cache = this->entryPoint;

	for (; cache; cache = cache->pNext) {
		if (cache == nullptr) { continue; } // if there are null pointers in double linked list at first layer
		else {
			ITEM10** secondLayer = (ITEM10**)cache->ppItems;
			for (int counter = 0; counter < 26; counter++) {
				if (secondLayer[counter]) {
					if (ItemsHandler::isInList(secondLayer[counter], itemID)) { 
						return ItemsHandler::getItemFromList(secondLayer[counter], itemID);
					}
				}
			}
		}
	}
	return nullptr;
}

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
	if (pNewItemID && isInStructure(pNewItemID)) {
		throw 1; // Already exists exception
	}

	if (pNewItemID == 0 || ItemsHandler::validateIDFormat(pNewItemID)) {
		ITEM10* newItem = (ITEM10*)GetItem(10, ((char*)pNewItemID));
		newItem->pNext = (ITEM10*)this->entryPoint->ppItems[0];
		this->entryPoint->ppItems[0] = newItem;
		this->size++;
	}

	else {
		throw 2; // Format error
	}
}

void DataStructure::insertItem(ITEM10* item) {
	item->pNext = (ITEM10*) *(this->entryPoint->ppItems);
	*(this->entryPoint->ppItems) = item;
	this->size++;
}

void DataStructure::removeItem(char* itemID) {
	if (itemID == nullptr || !ItemsHandler::validateIDFormat(itemID)) {
		throw 2; // Format error
	}
	else if (!isInStructure(itemID)) {
		throw 1; // No such thing in structure 
	}
	else {
		HEADER_E* cache = this->entryPoint;
		for (; cache; cache = cache->pNext) {
			if (cache == nullptr) { continue; }
			else {
				ITEM10** secondLayer = (ITEM10**)cache->ppItems;
				for (int counter = 0; counter < 26; counter++) {
					if (secondLayer[counter]) {
						if (ItemsHandler::isInList(secondLayer[counter], itemID)) {
							ItemsHandler::removeElementFromList(&secondLayer[counter], itemID);
							this->size--;
						}
					}
				}
			}
		}

	}
}

DataStructure::~DataStructure() { // works
	if (!this->entryPoint) { return; }
	for (; this->entryPoint; this->entryPoint = this->entryPoint->pNext) {
		for (int counter = 0; counter < 26; counter++) {
			ItemsHandler::freeList(&(((ITEM10**)this->entryPoint->ppItems)[counter]));
		}
	}
}

void DataStructure::operator+=(ITEM10* item) {
	item->pNext = (ITEM10*)this->entryPoint->ppItems[0];
	this->entryPoint->ppItems[0] = item;
	this->size++;
}

void DataStructure::operator-=(char* item) {
	removeItem(item);
}

DataStructure& DataStructure::operator=(DataStructure& right) {
	this->~DataStructure();
	
	return *this;
} 

int DataStructure::operator==(DataStructure& other) {
	if (this->size != other.getItemsNumber()) { return 0; }
	
	HEADER_E* cache = this->entryPoint;
	HEADER_E* otherCache = other.entryPoint;

	for (; cache || otherCache; cache = cache->pNext, otherCache = otherCache->pNext) {
		if (!cache && otherCache || cache && !otherCache) { return 0; }
		for (int counter = 0; counter < 26; counter++) {
			bool areSame = ItemsHandler::areSame(((ITEM10**)cache->ppItems)[counter],
												 ((ITEM10**)otherCache->ppItems)[counter]);
			if (!areSame) { return 0; }
		}
	}
	return 1;
}

std::vector <ITEM10> DataStructure::getAllItems() {
	HEADER_E* entryPoint = this->entryPoint;
	std::vector <ITEM10> result = {};
	for (; entryPoint; entryPoint = entryPoint->pNext) {
		for (int i = 0; i < 26; i++) {
			std::vector <ITEM10> cache = ItemsHandler::listToVector((ITEM10*) (entryPoint->ppItems)[i]);
			result.insert(result.end(), cache.begin(), cache.end());
		}
	}
	return result;
}