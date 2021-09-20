#pragma once
#include <iostream>
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"

namespace ItemsHandler {
	void printItem(ITEM10* item, size_t* currentNumber = 0);
	void printItemList(ITEM10* head, size_t* currentNumber = 0);
	void removeElementFromList(ITEM10** head, char* key);
	void freeList(ITEM10** list);
	ITEM10* getItemFromList(ITEM10* list, char* itemID);
	bool checkWord(char* word, int len);
	bool validateIDFormat(char* pNewItemID);
	bool isInList(ITEM10* head, char* itemID);
}