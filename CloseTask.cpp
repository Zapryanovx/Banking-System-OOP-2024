#include "CloseTask.h"


unsigned CloseTask::getAccountNumber() const
{
    return accountNumber;
}

void CloseTask::printTask() const
{
    std::cout << " CloseTask: " << getFirstName() << " "
              << getLastName() << " wants to close account with number" << accountNumber <<std::endl;
}

void CloseTask::viewTask() const
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "[Task ID]: " << getTaskId() << std::endl;
    std::cout << "[Task Type]: Close" << std::endl;
    std::cout << "[Requested By]: " << getFirstName() << " " << getLastName() << std::endl;
    std::cout << "[Account Number]: " << accountNumber << std::endl;
}

Task* CloseTask::clone() const
{
    Task* newObj = new (std::nothrow) CloseTask(*this);
    return newObj;
}