#pragma once
#include "MyString.h"

class Account
{
private:
    MyString firstName;
    MyString lastName;
    MyString EGN;
    unsigned age;
    MyString address;

    MyString bankName;

    static unsigned accountCounter;
    unsigned accountNumber;
    double balance = 0.00;

public:
    Account() = default;
    Account(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& address, const MyString& bankName);

    const MyString& getFirstName() const;
    const MyString& getLastName() const;
    const MyString& getEGN() const;
    unsigned getAge() const;
    const MyString& getAddress() const;
    const MyString& getBankName() const;

    unsigned getAccountNumber() const;

    void addBalance(double ammount);
    double getBalance() const;

    void printAccountData() const;

};