#pragma once
#include "Task.h"

class CloseTask : public Task 
{
private:
    unsigned accountNumber;

public:
    CloseTask(const MyString& firstName, const MyString& lastName,const MyString& EGN, unsigned age, const MyString& currBankName, unsigned accountNumber):
        Task(CLOSE, firstName, lastName, EGN, age, currBankName), accountNumber(accountNumber) {}

    unsigned getAccountNumber() const;
    Task* clone() const override;

    void printTask() const override;
    void viewTask() const override;
};