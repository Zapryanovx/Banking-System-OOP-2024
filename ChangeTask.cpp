#include "ChangeTask.h"

const MyString& ChangeTask::getNewBankName() const
{
    return newBankName;
}

unsigned ChangeTask::getAccountNumber() const
{
    return accountNumber;
}

Task* ChangeTask::clone() const 
{
    Task* newObj = new (std::nothrow) ChangeTask(*this);
    return newObj;
}

void ChangeTask::printTask() const
{
    std::cout << " ChangeTask: " << getFirstName() << " " << getLastName()
        << " wants to move his/her bank account here."<< std::endl;
}

void ChangeTask::viewTask() const
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "[Task ID]: " << getTaskId() << std::endl;
    std::cout << "[Task Type]: Change" << std::endl;
    std::cout << "[Requested By]: " << getFirstName() << " " << getLastName() << std::endl;
    std::cout << "[Account Number]: " << accountNumber << std::endl;
    std::cout << "[Old Bank Name]: " << currBankName << std::endl;
}
