#include "BankingSystem.h"
#include <iostream>

const Bank& BankingSystem::getBank(const MyString& bankName)  const
{
    size_t size = banks.getSize();
    for (int i = 0; i < size; i++)
    {
        if (banks[i].getBankName() == bankName)
        {
            return banks[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getBank Bank not found.");
}

Bank& BankingSystem::getBank(const MyString& bankName)
{
    size_t size = banks.getSize();
    for (int i = 0; i < size; i++)
    {
        if (banks[i].getBankName() == bankName)
        {
            return banks[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getBank Bank not found.");
}

BankingSystem& BankingSystem::getInstance()
{
    static BankingSystem instance;
    return instance;
}

void BankingSystem::addBank(const MyString& bankName)
{
    try
    {
        getBank(bankName);
        std::cout << "[ERROR] Bank already exists: " << bankName << std::endl;
    }
    catch (std::exception& err)
    {
        banks.pushBack(Bank(bankName));
        std::cout << "[SUCCESS] Bank added: " << bankName << std::endl;
    }

}

void BankingSystem::removeBank(const MyString& bankName)
{
    size_t size = banks.getSize();
    for (int i = 0; i < size; i++)
    {
        if (banks[i].getBankName() == bankName)
        {
            banks.popAt(i);
            std::cout << "[SUCCESS] Bank removed: " << bankName << std::endl;
            return;
        }
    }

    throw std::exception("[ERROR] BankingSystem::remove Bank not found.");
}

void BankingSystem::printAllBanks() const
{
    std::cout << "[LIST] Banks in the system:" << std::endl;

    size_t size = banks.getSize();
    for (int i = 0; i < size; i++)
    {
        std::cout << "[" << i << "] " << banks[i].getBankName() << std::endl;
    }
}

void BankingSystem::addExternEmployee(const ExternEmployee& externEmployee)
{
    externEmployees.pushBack(externEmployee);
}

void BankingSystem::removeExternEmployee(const ExternEmployee& externEmployee)
{
    size_t size = externEmployees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (externEmployees[i].getEGN() == externEmployee.getEGN())
        {
            externEmployees.popAt(i);
            return;
        }
    }

    throw std::exception("[ERROR] Bank::removeExtermEmployee Extern employee not found.");
}

void BankingSystem::addEmployee(const Employee& employee)
{
    employees.pushBack(employee);
}

void BankingSystem::removeEmployee(const Employee& employee)
{
    size_t size = employees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (employees[i].getEGN() == employee.getEGN())
        {
            employees.popAt(i);
            return;
        }
    }

    throw std::exception("[ERROR] Bank::removeEmployee Employee not found.");
}

void BankingSystem::addClient(const Client& client)
{
    clients.pushBack(client);
}

void BankingSystem::removeClient(const Client& client)
{
    size_t size = clients.getSize();
    for (int i = 0; i < size; i++)
    {
        if (clients[i].getEGN() == client.getEGN())
        {
            clients.popAt(i);
            return;
        }
    }

    throw std::exception("[ERROR] Bank::removeClient Client not found.");
}

const ExternEmployee& BankingSystem::getExternEmployee(const MyString& EGN) const
{
    size_t size = externEmployees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (externEmployees[i].getEGN() == EGN)
        {
            return externEmployees[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getExternEmployee Extern employee not found.");
}

ExternEmployee& BankingSystem::getExternEmployee(const MyString& EGN)
{
    size_t size = externEmployees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (externEmployees[i].getEGN() == EGN)
        {
            return externEmployees[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getExternEmployee Extern employee not found.");
}


const Employee& BankingSystem::getEmployee(const MyString& EGN) const
{
    size_t size = employees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (employees[i].getEGN() == EGN)
        {
            return employees[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getEmployee Employee not found.");
}

Employee& BankingSystem::getEmployee(const MyString& EGN)
{
    size_t size = employees.getSize();
    for (int i = 0; i < size; i++)
    {
        if (employees[i].getEGN() == EGN)
        {
            return employees[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getEmployee Employee not found.");
}

void  BankingSystem::addCheque(const Cheque& cheque)
{
    cheques.pushBack(cheque);
}

void  BankingSystem::removeCheque(const Cheque& cheque)
{
    size_t size = cheques.getSize();
    for (int i = 0; i < size; i++)
    {
        if (cheques[i].getUniqueCode() == cheque.getUniqueCode())
        {
            cheques.popAt(i);
            return;
        }
    }

    throw std::exception("[ERROR] Bank::removeCheque Cheque not found.");
}

const Cheque& BankingSystem::getCheque(const MyString& uniqueCode) const
{
    size_t size = cheques.getSize();
    for (int i = 0; i < size; i++)
    {
        if (cheques[i].getUniqueCode() == uniqueCode)
        {
            return cheques[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getCheque Cheque not found.");
}

const Client& BankingSystem::getClient(const MyString& EGN) const
{
    size_t size = clients.getSize();
    for (int i = 0; i < size; i++)
    {
        if (clients[i].getEGN() == EGN)
        {
            return clients[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getClient Client not found.");
}

Client& BankingSystem::getClient(const MyString& EGN)
{
    size_t size = clients.getSize();
    for (int i = 0; i < size; i++)
    {
        if (clients[i].getEGN() == EGN)
        {
            return clients[i];
        }
    }

    throw std::exception("[ERROR] BankingSystem::getClient Client not found.");

}

const Vector<Employee>& BankingSystem::getEmployees() const
{
    return employees;
}

Vector<Employee>& BankingSystem::getEmployees()
{
    return employees;
}

const Vector<Client>& BankingSystem::getClients() const
{
    return clients;
}

Vector<Client>& BankingSystem::getClients()
{
    return clients;
}

const Vector<ExternEmployee>& BankingSystem::getExternEmployees() const
{
    return externEmployees;
}

Vector<ExternEmployee>& BankingSystem::getExternEmployees()
{
    return externEmployees;
}