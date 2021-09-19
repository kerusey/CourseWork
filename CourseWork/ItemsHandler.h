#pragma once
#include <iostream>
#include "Items.h"
#include "Headers.h"

namespace ItemsHandler {
	void printItem(ITEM10* item, size_t currentNumber);
	void printItemList(ITEM10* head, size_t currentNumber);
	size_t getSizeOfSecondLayerArray(ITEM10** list);
}