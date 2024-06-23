#pragma once
#include "Task.h"

class ChangeTask : public Task
{
private:
    unsigned accountNumber;
    MyString currBankName;
    MyString newBankName;

public:
    ChangeTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, unsigned accountNumber, const MyString& currBankName, const MyString& newBankName):
        Task(CHANGE, firstName, lastName, EGN, age, currBankName), accountNumber(accountNumber), newBankName(newBankName) {}

    const MyString& getNewBankName() const;
    unsigned getAccountNumber() const;
    Task* clone() const override;

    void printTask() const override;
    void viewTask() const override;
};