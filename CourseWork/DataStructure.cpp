#include "DataStructure.h"

#pragma warning (disable: 4996)

DataStructure::DataStructure(HEADER_E* generatedStructure, size_t size): 
	entryPoint (generatedStructure), size(size) {}

DataStructure::DataStructure(DataStructure& original) {
	DataStructure* cache = copyElements(original);
	this->entryPoint = cache->entryPoint;
	this->size = cache->size;
}

DataStructure::DataStructure() :
	entryPoint(nullptr), size(0) {}

DataStructure::DataStructure(char* filename) {
	FILE* pFile = fopen(filename, "rb");
	char* pData;
	long lSize;
	if (pFile) {
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);
		pData = (char*)malloc(lSize);
		int n = fread(pData, 1, lSize, pFile);
		fclose(pFile);
	}
	else { std::cout << "file error" << std::endl; return; }

	DataStructure* newDataStruct = new DataStructure(GetStruct5(10, 1), 1);
	ITEM10 itemToBeRemoved = newDataStruct->getAllItems()[0];
	newDataStruct->insertItem((char*)"Danila Likh"); // setting up static cache entry point 
	newDataStruct->removeItem(itemToBeRemoved.pID);
	char* cursor;
	int totalItems = 0;
	memcpy(&totalItems, cursor = pData, sizeof(int));
	cursor += sizeof(int);
	for (int i = 0; i < totalItems; i++) {
		int pIdSize = 0;
		char* pID;
		unsigned long int code = 0;
		int day = 0,
			year = 0;
		char* month;
		memcpy(&pIdSize, cursor, sizeof(int));
		pID = (char*)malloc(pIdSize * sizeof(char));
		memcpy(pID, cursor += sizeof(int), pIdSize);
		memcpy(&code, cursor += pIdSize, sizeof(unsigned long int));
		memcpy(&day, cursor += sizeof(int), sizeof(int));
		memcpy(&month, cursor += sizeof(char*), sizeof(int));
		memcpy(&year, cursor += sizeof(int), sizeof(int));
		cursor += sizeof(int);
		ITEM10* pointer = (ITEM10*)GetItem(10, pID);
		pointer->Date.Day = day;
		pointer->Date.pMonth = month;
		pointer->Date.Year = year;
		pointer->Code = code;
		pointer->pID = pID;

		newDataStruct->insertItem(*pointer);
	}
	newDataStruct->removeItem((char*)"Danila Likh"); // removing it

	this->entryPoint = newDataStruct->entryPoint;
	this->size = newDataStruct->size;
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

void DataStructure::insertItem(ITEM10& item) {
	ITEM10* newNode = (ITEM10*) malloc(sizeof(ITEM10));

	newNode->Code = item.Code;
	newNode->pID = item.pID;
	newNode->Date.Day = item.Date.Day;
	newNode->Date.pMonth = item.Date.pMonth;
	newNode->Date.Year = item.Date.Year;

	newNode->pNext = (ITEM10*) *(this->entryPoint->ppItems);
	*(this->entryPoint->ppItems) = newNode;
	
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
	DataStructure* newOne = copyElements(right);
	this->entryPoint = newOne->entryPoint;
	this->size = newOne->size;
	return *this;
} 

int DataStructure::operator==(DataStructure& other) {
	if (this->size != other.getItemsNumber()) { return 0; }
	std::vector <ITEM10> thisItems = this->getAllItems();
	std::vector <ITEM10> otherItems = other.getAllItems();
	for (int i = 0; i < thisItems.size(); i++) {
		if (!ItemsHandler::areSame(&thisItems[i], &otherItems[i])) { return 0; }
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
	reverse(result.begin(), result.end());
	return result;
}

DataStructure* DataStructure::copyElements(DataStructure& original) {
	std::vector <ITEM10> itemsToBeAppended = original.getAllItems();
	DataStructure* newDataStruct = new DataStructure(GetStruct5(10, 1), 1);
	ITEM10 itemToBeRemoved = newDataStruct->getAllItems()[0];
	newDataStruct->insertItem((char*) "Danila Likh"); // setting up static cache entry point 
	newDataStruct->removeItem(itemToBeRemoved.pID);
	for (int i = 0; i < itemsToBeAppended.size(); i++) { newDataStruct->insertItem(itemsToBeAppended[i]); }
	newDataStruct->removeItem((char*)"Danila Likh"); // removing it
	return newDataStruct;
}

void DataStructure::write(char* filename) {
	FILE* pFile = fopen(filename, "wb");
	if (!pFile) { std::cout << "File not opened" << std::endl; return; }

	std::vector <ITEM10> itemsToBeWritten = this->getAllItems();
	char* totalNum = (char*)malloc(sizeof(int));
	
	memcpy(totalNum, &this->size, sizeof(int));
	fwrite(totalNum, 1, sizeof(int), pFile);
	for (int i = 0; i < this->size; i++) {
		size_t n = 0;
		char* serialized = ItemsHandler::serializeItem(&itemsToBeWritten[i], &n);
		fwrite(serialized, 1, n, pFile);
	}

	fclose(pFile);
}