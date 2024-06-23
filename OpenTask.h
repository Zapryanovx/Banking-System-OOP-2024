#pragma once
#include "Task.h"

class OpenTask : public Task
{
public:
    OpenTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& currBankName):
        Task(OPEN, firstName, lastName, EGN, age, currBankName) {}

    Task* clone() const override;

    void printTask() const override;
    void viewTask() const override;
};