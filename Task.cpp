#include "Task.h"

unsigned Task::taskCounter = 0;

Task::Task(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& currBankName):
    type(type), firstName(firstName), lastName(lastName), EGN(EGN), age(age), currBankName(currBankName)
{
    taskCounter++;
    taskId = taskCounter;
}

unsigned Task::getTaskId() const
{
    return taskId;
}

TaskType Task::getType() const 
{
    return type;
}

const MyString& Task::getFirstName() const
{
    return firstName;
}

const MyString& Task::getLastName() const
{
    return lastName;
}

const MyString& Task::getEGN() const
{
    return EGN;
}

const MyString& Task::getCurrBankName() const
{
    return currBankName;
}