#include "ItemsHandler.h"

void ItemsHandler::printItem(ITEM10* item, size_t* currentNumber) { // should be fine 
	std::cout << *currentNumber << ") " <<
				 item->pID << " " <<
				 item->Code << " " <<
				 item->Date.Day << " " <<
				 item->Date.pMonth << " " <<
				 item->Date.Year << std::endl;
	(*currentNumber)++;
}

void ItemsHandler::printItemList(ITEM10* head, size_t* currentNumber) {
	for (; head; head = head->pNext) {
		printItem(head, currentNumber);
	}
}

bool ItemsHandler::checkWord(char* word, int len) {
	for (int i = 0; i < len; i++) {
		int ascii = (int) *(word + i);
		if (!((ascii >= 65 || ascii <= 90) || (ascii >= 97 || ascii <= 122) || ascii == 45)) { return true; }
	}
	return false;
}

bool ItemsHandler::validateIDFormat(char* pNewItemID) {
	if (strlen(pNewItemID) < 3) { return false; }
	
	char* spacePos = strchr(pNewItemID, ' ');
	
	if (spacePos == 0 || strchr(spacePos + 1, ' ') != 0) { return false; }

	char first = *pNewItemID,
		 second = *(spacePos + 1);

	if ((int)first < 65 || (int)first > 90 || (int)second < 65 || (int)second > 90) { return false; }
	
	int lenFirst = spacePos - pNewItemID,
		lenSecond = strlen(pNewItemID) - lenFirst - 1;

	if (checkWord(pNewItemID, lenFirst) || checkWord(spacePos + 1, lenSecond)) { return false; }
	return true;
}

bool ItemsHandler::isInList(ITEM10* head, char* itemID) {
	for (; head; head = head->pNext) {
		if ((std::string) head->pID == (std::string) itemID) { return true; }
	}
	return false;
}