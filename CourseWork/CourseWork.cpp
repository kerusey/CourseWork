#include <iostream>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
// IMPORTANT: follow the given order of *.h files: ICS0017DataSource.h must be
// the last
int main()
{
	HEADER_C* p = GetStruct2(3, 100);
	ITEM3* pNewItem = (ITEM3*)GetItem(3);
	return 0;
}
