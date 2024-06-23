#include "OpenTask.h"

void OpenTask::printTask() const
{
    std::cout << " OpenTask: " << getFirstName() << " " << getLastName()
              <<" wants to open an account." << std::endl;
}

void OpenTask::viewTask() const
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "[Task ID]: " << getTaskId() << std::endl;
    std::cout << "[Task Type]: Open" << std::endl;
    std::cout << "[Requested By]: " << getFirstName() << " " << getLastName() << std::endl;
}

Task* OpenTask::clone() const 
{
    Task* newObj = new (std::nothrow) OpenTask(*this); 
    return newObj;
}