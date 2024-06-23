#pragma once
#include "MyString.h"

class Cheque
{
private:
	MyString uniqueCode;
	unsigned ammount;
public:
	Cheque() = default;
	Cheque(const MyString& uniqueCode, unsigned ammount): 
		uniqueCode(uniqueCode), ammount(ammount) {}

	const MyString& getUniqueCode() const;
	unsigned getAmmount() const;

};

