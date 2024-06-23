#pragma once
#include "User.h"
#include "Cheque.h"

class BankingSystem;
class ExternEmployee : public User
{
public:
    ExternEmployee() = default;
    ExternEmployee(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& password):
        User(firstName, lastName, EGN, age, password, UserType::EXTERN_EMPLOYEE) {}
   
    void sendCheck(double amount, const MyString& uniqueCode, const MyString& EGN, BankingSystem& bankingSystem) const;
    bool isAlnum(const MyString& uniqueCode) const;
    bool isUniqueCodeValid(const BankingSystem& bankingSystem, const MyString& uniqueCode) const;
    bool isCodeUnique(const BankingSystem& bankingSystem, const MyString& uniqueCode) const;
};
