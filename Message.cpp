#include "Message.h"

void Message::printMessage() const
{
	std::cout << message << std::endl;
}

const MyString& Message::getMessage() const
{
	return message;
}