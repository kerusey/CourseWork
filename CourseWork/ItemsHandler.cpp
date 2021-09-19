#include "ItemsHandler.h"

void ItemsHandler::printItem(ITEM10* item, size_t currentNumber) {
	std::cout << currentNumber << " " <<
				 item->pID << " " <<
				 item->Code << " " <<
				 item->Date.Day << " " <<
				 // item->Date.pMonth << " " << 
				 item->Date.Year << std::endl;
}

void ItemsHandler::printItemList(ITEM10* head, size_t currentNumber) {
	
		std::cout << head->pID << std::endl;
		try {
			std::cout << head->pNext->pID << std::endl;
		}
		catch (...) {
			return;
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
