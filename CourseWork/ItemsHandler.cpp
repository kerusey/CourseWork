#include "ItemsHandler.h"

void ItemsHandler::printItem(ITEM10* item, size_t* currentNumber) { // should be fine 
	if (!item) { std::cout << "Nothing to print!" << std::endl; }

	if (currentNumber) {
		std::cout << *currentNumber << ") " <<
					  item->pID << " " <<
					  item->Code << " " <<
					  item->Date.Day << " " <<
					  item->Date.pMonth << " " <<
					  item->Date.Year << std::endl;
		(*currentNumber)++;
	}

	else {
		std::cout << item->pID << " " <<
					 item->Code << " " <<
					 item->Date.Day << " " <<
					 item->Date.pMonth << " " <<
					 item->Date.Year << std::endl;
	}
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

void ItemsHandler::removeElementFromList(ITEM10** head, char* key) {
	ITEM10* temp = *head;
	ITEM10* prev = nullptr;

	if (temp && (std::string) temp->pID == (std::string) key) {
		*head = temp->pNext;
		delete temp;
		return;
	}

	else {
		while (temp && (std::string) temp->pID != (std::string) key) {
			prev = temp;
			temp = temp->pNext;
		}

		if (!temp) { return; }
		prev->pNext = temp->pNext;
		delete temp;
	}
	
}

void ItemsHandler::freeList(ITEM10** list) { // works pretty fine 
	if (!list) { return; }
	ITEM10* current = *list;
	ITEM10* next = nullptr;

	for (; current; current->pNext) {
		next = current->pNext;
		free(current);
		current = next;
	}
	*list = nullptr;

}

ITEM10* ItemsHandler::getItemFromList(ITEM10* list, char* itemID) {
	for (; list; list = list->pNext) {
		if ((std::string)list->pID == (std::string)itemID) { 
			list->pNext = nullptr;
			return list; 
		}
	}
}

bool ItemsHandler::areSame(ITEM10* list1, ITEM10* list2) {
	for (; list1 || list2; list1 = list1->pNext, list2 = list2->pNext) {
		if (!list1 && list2 || list1 && !list2) { return false; }
		if (!(
				(list1->Code == list2->Code) &&
				((std::string) list1->pID == (std::string)list2->pID) &&
				(list1->Date.Day == list2->Date.Day) &&
				((std::string) list1->Date.pMonth == (std::string) list2->Date.pMonth) &&
				(list1->Date.Year == list2->Date.Year)
			)) { return false; }
	}
	return true;
}

ITEM10* ItemsHandler::copyList(ITEM10* head) { // Works 
	if (!head) { return nullptr; }

	ITEM10* newNode = (ITEM10*) malloc(sizeof(ITEM10));

	newNode->Code = head->Code;
	newNode->pID = head->pID;
	newNode->Date.Day = head->Date.Day;
	newNode->Date.pMonth = head->Date.pMonth;
	newNode->Date.Year = head->Date.Year;

	newNode->pNext = copyList(head->pNext);

	return newNode;
}

std::vector <ITEM10> ItemsHandler::listToVector(ITEM10* head) {
	std::vector <ITEM10> responce;
	for (; head; head = head->pNext) { 
		ITEM10 cache = *head;
		cache.pNext = nullptr;
		responce.push_back(cache);
	}
	return responce;
}
