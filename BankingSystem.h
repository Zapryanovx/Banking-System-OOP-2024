#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Bank.h"
#include "ExternEmployee.h"

class BankingSystem
{
private:
    Vector<Bank> banks;
    Vector<ExternEmployee> externEmployees;
    Vector<Employee> employees;
    Vector<Client> clients;

    Vector<Cheque> cheques;

    BankingSystem() = default;

public:

    BankingSystem(const BankingSystem& other) = delete;
    BankingSystem& operator=(const BankingSystem& other) = delete;


    static BankingSystem& getInstance();

    void addBank(const MyString& bankName);
    void removeBank(const MyString& bankName);
    void printAllBanks() const;

    void addExternEmployee(const ExternEmployee& externEmployee);
    void removeExternEmployee(const ExternEmployee& externEmployee);

    void addEmployee(const Employee& employee);
    void removeEmployee(const Employee& employee);

    void addClient(const Client& client);
    void removeClient(const Client& client);

    void addCheque(const Cheque& cheque);
    void removeCheque(const Cheque& cheque);

    const Bank& getBank(const MyString& bankName) const;
    Bank& getBank(const MyString& bankName);

    const Client& getClient(const MyString& EGN) const;
    Client& getClient(const MyString& EGN);

    const Employee& getEmployee(const MyString& EGN) const;
    Employee& getEmployee(const MyString& EGN);

    const ExternEmployee& getExternEmployee(const MyString& EGN) const;
    ExternEmployee& getExternEmployee(const MyString& EGN);

    const Cheque& getCheque(const MyString& uniqueCode) const;

    const Vector<Employee>& getEmployees() const;
    Vector<Employee>& getEmployees();

    const Vector<Client>& getClients() const;
    Vector<Client>& getClients();

    const Vector<ExternEmployee>& getExternEmployees() const;
    Vector<ExternEmployee>& getExternEmployees();

};