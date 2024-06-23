#include "Employee.h"
#include "Bank.h"
#include "BankingSystem.h"

void Employee::addTask(const polymorphic_ptr<Task>& task)
{
    tasks.pushBack(task);
}

void Employee::viewTask(unsigned taskId) const
{
    if (taskId >= tasks.getSize())
    {
        std::cout << "[ERROR] Invalid taskId." << std::endl;
        return;
    }

    tasks[taskId]->viewTask();
}

void Employee::openAccount(Client& client)
{
    Account newAccount(client.getFirstName(), client.getLastName(), client.getEGN(), client.getAge(), client.getAddress(), bankPtr->getBankName());
    bankPtr->addAccount(newAccount);
    client.addAccount(newAccount);

    try
    {
        const Client& clientFind = bankPtr->getClient(client.getEGN());
    }
    catch (std::exception& e)
    {
        bankPtr->addClient(client);
    }
}

void Employee::transferAccount(const Account& oldAccount, Client& client)
{
    Account newAccount(client.getFirstName(), client.getLastName(), client.getEGN(), client.getAge(), client.getAddress(), bankPtr->getBankName());

    try
    {
        newAccount.addBalance(oldAccount.getBalance());
    }
    catch (...){}

    bankPtr->addAccount(newAccount);
    BankingSystem::getInstance().getClient(client.getEGN()).addAccount(newAccount);
    client.addAccount(newAccount);

    try
    {
        const Client& clientFind = bankPtr->getClient(client.getEGN());
    }
    catch (std::exception& e)
    {
        bankPtr->addClient(client);
    }
}


void Employee::closeAccount(Client& client, const Account& account)
{
    client.removeAccount(account);
    bankPtr->removeAccount(account);

    if (bankPtr->getClient(client.getEGN()).getAccounts().getSize() == 0)
    {
        bankPtr->removeClient(client);
    }
}

void Employee::approveTask(Client& client, unsigned taskId)
{
    if (taskId >= tasks.getSize())
    {
        std::cout << "[ERROR] Invalid taskId." << std::endl;
        return;
    }

    TaskType type = tasks[taskId]->getType();
    if(type == OPEN)
    {
        BankingSystem::getInstance().getEmployee(EGN).openAccount(client);
        std::cout << "[SUCCESS] Account opened successfully." << std::endl;
        BankingSystem::getInstance().getClient(client.getEGN()).receiveMessage("[SUCCESS] Your request has been approved.");

        tasks.popAt(taskId);
    }

    else if (type == CLOSE)
    {
        try
        {
            CloseTask* closeTask = static_cast<CloseTask*> (tasks[taskId].get());
            unsigned accountNumber = closeTask->getAccountNumber();
            const Account& account = bankPtr->getAccount(accountNumber);

            if (account.getEGN() == client.getEGN())
            {
               
                BankingSystem::getInstance().getEmployee(EGN).closeAccount(client, account);
                std::cout << "[SUCCESS] Account closed successfully." << std::endl;
                BankingSystem::getInstance().getClient(client.getEGN()).receiveMessage("[SUCCESS] Your request has been approved.");

                tasks.popAt(taskId);
            }

            else
            {
                BankingSystem::getInstance().getClient(client.getEGN()).receiveMessage("[ERROR] You does not own an account with number " + accountNumber);

                std::cout << "[ERROR] Client has provided invalid data." << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

    }

    else
    {
        std::cout << "[ERROR] Invalid command for type CHANGE." << std::endl;
    }
   
}

void Employee::disapproveTask(Client& client, unsigned taskId, const MyString& message)
{
    if (taskId >= tasks.getSize())
    {
        std::cout << "[ERROR] Invalid taskId." << std::endl;
        return;
    }

    MyString fullMessage = "[" + bankPtr->getBankName() + "]" + client.getFirstName() + " " + client.getLastName() + ", " + message;
    BankingSystem::getInstance().getClient(client.getEGN()).receiveMessage(fullMessage);
    std::cout << "[SUCCESS] Task disapproved, id: " << taskId + 1 << std::endl;
    tasks.popAt(taskId);

}

bool Employee::isMatch(const Account& account, const Client& client)
{
    return account.getEGN() == client.getEGN()
        && account.getFirstName() == client.getFirstName()
        && account.getLastName() == client.getLastName()
        && account.getAge() == client.getAge()
        && account.getAddress() == client.getAddress();
}

void Employee::validateTask(Bank& oldBank, Client& client, unsigned taskId)
{
    if (taskId >= tasks.getSize())
    {
        std::cout << "[ERROR] Invalid taskId." << std::endl;
        return;
    }

    ChangeTask* changeTask = static_cast<ChangeTask*> (tasks[taskId].get());
    unsigned accountNumber = changeTask->getAccountNumber();

    if (tasks[taskId]->getType() == CHANGE)
    {
 
        if (oldBank.hasAccount(accountNumber))
        {
            const Account& oldAccount = oldBank.getAccount(accountNumber);
            if (isMatch(oldAccount, client))
            {

                BankingSystem::getInstance().getEmployee(EGN).transferAccount(oldAccount, client);
                BankingSystem::getInstance().getBank(changeTask->getCurrBankName()).removeAccount(oldAccount);
                BankingSystem::getInstance().getClient(client.getEGN()).receiveMessage("[SUCCESS] Your account has been successfully transferred.");

                std::cout << "[SUCCESS] Task validated and account transferred: " << taskId << std::endl;
                tasks.popAt(taskId);
            }

            else
            {
                std::cout << "[ERROR] Validation failed: Invalid data provided." << std::endl;
            }
        }

        else
        {
            std::cout << "[ERROR] No account found." << std::endl;
        }
    }

    else
    {
        std::cout << "[ERROR] Invalid command for type OPEN/CLOSE." << std::endl;
    }
}

void Employee::showTasks() const 
{
    size_t size = tasks.getSize();
    
    if (size == 0)
    {
        std::cout << "[DONE] You have no tasks to do." << std::endl;
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << "[Task " << i + 1 << "]" << "----------------------------------------" << std::endl;
        tasks[i]->printTask();
    }
}

const Bank& Employee::getBank() const
{
    return *bankPtr;
}

const Vector<polymorphic_ptr<Task>>& Employee::getTasks() const
{
    return tasks;
}

Vector<polymorphic_ptr<Task>>& Employee::getTasks()
{
    return tasks;
}