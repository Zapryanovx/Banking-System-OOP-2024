#pragma once
#include "MyString.h"

class Message
{
private:
	MyString message;

public:
	Message() = default;
	Message(const MyString& message) : message(message) {};

	void printMessage() const;
	const MyString& getMessage() const;
};

