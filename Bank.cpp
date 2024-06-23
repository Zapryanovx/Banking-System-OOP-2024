#include "Bank.h"
#include "BankingSystem.h"

bool Bank::hasAccount(unsigned accountNumber) 
{
	size_t size = accounts.getSize();
	for (int i = 0; i < size; i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
		{
			return true;
		}
	}

	return false;
}

const Account& Bank::getAccount(unsigned accountNumber) const
{
	size_t size = accounts.getSize();
	for (int i = 0; i < size; i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
		{
			return accounts[i];
		}
	}

	throw std::exception("[ERROR] Bank::getAccount Account not found.");
}


Account& Bank::getAccount(unsigned accountNumber)
{
	size_t size = accounts.getSize();
	for (int i = 0; i < size; i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
		{
			return accounts[i];
		}
	}

	throw std::exception("[ERROR] Bank::getAccount Account not found.");
}

void Bank::addAccount(const Account& account)
{
	accounts.pushBack(account);
}

void Bank::removeAccount(const Account& account)
{
	size_t size = accounts.getSize();
	for (int i = 0; i < size; i++)
	{
		if (account.getAccountNumber() == accounts[i].getAccountNumber())
		{
			accounts.popAt(i);
			return;
		}
	}

	throw std::exception("[ERROR] Bank::removeAccount Account not found.");
}

void Bank::addClient(const Client& client)
{
	clients.pushBack(client);
}

void Bank::removeClient(const Client& client)
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

void Bank::addEmployee(const Employee& employee)
{
	employees.pushBack(employee);
}

void Bank::removeEmployee(const Employee& employee)
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

const MyString& Bank::getBankName() const
{
	return bankName;
}

const Vector<Account>& Bank::getAccounts() const
{
	return accounts;
}

const Client& Bank::getClient(const MyString& EGN) const
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

const Vector<Client>& Bank::getClients() const
{
	return clients;
}

Vector<Client>& Bank::getClients() 
{
	return clients;
}


const Employee& Bank::getEmployee(const MyString& EGN) const
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
const Vector<Employee>& Bank::getEmployees() const
{
	return employees;
}

Vector<Employee>& Bank::getEmployees()
{
	return employees;
}

Employee& Bank::findLeastBusyEmployee()
{
	if (employees.getSize() == 0)
	{
		throw std::exception("[ERROR] No employees in the bank.");
	}

	unsigned leastBusyEmployee = 0;
	size_t minTasks = employees[0].getTasks().getSize();

	size_t size = employees.getSize();
	for (int i = 1; i < size; i++)
	{
		size_t taskCount = employees[i].getTasks().getSize();
		if (taskCount < minTasks) 
		{
			leastBusyEmployee = i;
			minTasks = taskCount;
		}
	}

	return employees[leastBusyEmployee];
}

void Bank::assignTask(const polymorphic_ptr<Task>& task)
{
	if (employees.getSize() == 0) 
	{
		std::cout << "[ERROR] No employees in the bank." << std::endl;
		return;
	}
	

	Employee& leastBusyEmployee = findLeastBusyEmployee();
	BankingSystem::getInstance().getEmployee(leastBusyEmployee.getEGN()).addTask(task);

	leastBusyEmployee.addTask(task);
	tasks.pushBack(task); 
	std::cout << "[SUCCESS] Your request has been sent." << std::endl;
}

const Vector<polymorphic_ptr<Task>>& Bank::getTasks() const
{
	return tasks;
}