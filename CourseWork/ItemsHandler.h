#pragma once
#include <iostream>
#include <vector>
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"

namespace ItemsHandler {
	void printItem(ITEM10* item, size_t* currentNumber = 0);
	void printItemList(ITEM10* head, size_t* currentNumber = 0);
	void removeElementFromList(ITEM10** head, char* key);
	void freeList(ITEM10** list);
	ITEM10* copyList(ITEM10* head);
	ITEM10* getItemFromList(ITEM10* list, char* itemID);
	bool checkWord(char* word, int len);
	bool areSame(ITEM10* list1, ITEM10* list2);
	bool validateIDFormat(char* pNewItemID);
	std::vector <ITEM10> listToVector(ITEM10* head);
	bool isInList(ITEM10* head, char* itemID);
}