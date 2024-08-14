#pragma once
#include "BookInfo.h"
#include <string>

class LoanManager {
private:
	void checkoutBook(BookInfo*);
	bool processYesNo();
public:
	void checkoutProcess(BookInfo*);
};

