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

size_t ItemsHandler::getSizeOfSecondLayerArray(ITEM10** list) { // works 
	size_t size = 0;
	for(int counter = 0; counter < 26; counter++) {
		if (*(list + counter)) {
			size++;
		}
	}
	return size;
}
