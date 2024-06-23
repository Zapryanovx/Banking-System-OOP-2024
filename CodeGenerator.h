#pragma once
#include "MyString.h"

class CodeGenerator
{
public:
	virtual const MyString& generateCode() = 0;
	virtual ~CodeGenerator();
};

