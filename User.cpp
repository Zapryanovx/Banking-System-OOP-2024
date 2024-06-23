#include "User.h"

const MyString& User::getFirstName() const 
{ 
	return firstName;
}

const MyString& User::getLastName() const 
{ 
	return lastName; 
}

const MyString& User::getEGN() const
{ 
	return EGN; 
}

unsigned User::getAge() const
{
	return age; 
}

bool User::validatePassword(const MyString& password) const
{
	return this->password == password;
}

UserType User::getTypeUser() const
{
	return typeUser;
}


void User::printUserInfo() const 
{
    std::cout << "[WHOAMI] User Information:" << std::endl;
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "EGN: " << EGN << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "User Type: ";

    switch (typeUser) 
    {
        case UserType::CLIENT:
            std::cout << "Client" << std::endl;
            break;
        case UserType::EMPLOYEE:
            std::cout << "Employee" << std::endl;
            break;
        case UserType::EXTERN_EMPLOYEE:
            std::cout << "Extern Employee" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
    }
}