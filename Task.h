#pragma once
#include "MyString.h"
#include <iostream>

enum TaskType 
{
    OPEN,
    CLOSE, 
    CHANGE 
};

class Task 
{
private:
    static unsigned taskCounter;
    unsigned taskId;
    TaskType type;

protected:
    MyString firstName;
    MyString lastName;
    MyString EGN;
    unsigned age;
    MyString currBankName;

public:
    Task(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& currBankName);
    virtual ~Task() {}

    unsigned getTaskId() const;
    TaskType getType() const;

    virtual const MyString& getFirstName() const;
    virtual const MyString& getLastName() const;
    virtual const MyString& getEGN() const;
    virtual const MyString& getCurrBankName() const;

    virtual Task* clone() const = 0;

    virtual void printTask() const = 0;
    virtual void viewTask() const = 0;
};