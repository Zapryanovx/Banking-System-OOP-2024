#pragma once
#include "MyString.h"

enum class UserType
{
    CLIENT,
    EMPLOYEE,
    EXTERN_EMPLOYEE,
    NONE
};

class User
{
protected:
    MyString firstName;
    MyString lastName;
    MyString EGN;
    unsigned age;
    MyString password;
    UserType typeUser; 

public:
    User() = default;
    User(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& password, UserType typeUser)
        : firstName(firstName), lastName(lastName), EGN(EGN), age(age), password(password), typeUser(typeUser) {}

    const MyString& getFirstName() const;
    const MyString& getLastName() const;
    const MyString& getEGN() const;
    unsigned getAge() const;
    bool validatePassword(const MyString& password) const;
    UserType getTypeUser() const;

    void printUserInfo() const;
};
