#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Account.h"
#include "Employee.h"
#include "Client.h"
#include "polymorphic_ptr.hpp"
#include "Task.h"

class Bank
{
private:
    MyString bankName;
    Vector<Account> accounts;
    Vector<Client> clients;
    Vector<Employee> employees;
    Vector<polymorphic_ptr<Task>> tasks;

public:
    Bank() = default;
    Bank(const MyString& bankName) : bankName(bankName) {}

    bool hasAccount(unsigned accountNumber);
    void addAccount(const Account& account);
    void removeAccount(const Account& account);

    void addClient(const Client& client);
    void removeClient(const Client& client);

    void addEmployee(const Employee& employee);
    void removeEmployee(const Employee& employee);

    const MyString& getBankName() const;

    const Account& getAccount(unsigned accountNumber) const;
    Account& getAccount(unsigned accountNumber);

    const Vector<Account>& getAccounts() const;

    const Client& getClient(const MyString& EGN) const;
    const Vector<Client>& getClients() const;
    Vector<Client>& getClients();
   
    const Employee& getEmployee(const MyString& EGN) const;
    const Vector<Employee>& getEmployees() const;
    Vector<Employee>& getEmployees();

    Employee& findLeastBusyEmployee();
    void assignTask(const polymorphic_ptr<Task>& task);

    const Vector<polymorphic_ptr<Task>>& getTasks() const;
    
};