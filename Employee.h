#pragma once
#include "User.h"
#include "Vector.hpp"
#include "polymorphic_ptr.hpp"
#include "Task.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include "Client.h"

class Bank;

class Employee : public User 
{
private:
    Vector<polymorphic_ptr<Task>> tasks;
    Bank* bankPtr;

    bool isMatch(const Account& account, const Client& client);
    void openAccount(Client& client);
    void transferAccount(const Account& oldAccount, Client& client);

    void closeAccount(Client& client, const Account& account);

public:
    Employee() = default;
    Employee(const MyString& firstName, const MyString& lastName, const MyString& EGN, int age, const MyString& password, Bank* bankPtr): 
        User(firstName, lastName, EGN, age, password, UserType::EMPLOYEE), bankPtr(bankPtr) {}

    void addTask(const polymorphic_ptr<Task>& task);
    void viewTask(unsigned taskId) const;
    void approveTask(Client& client, unsigned taskId);
    void disapproveTask(Client& client, unsigned taskId, const MyString& message);
    void validateTask(Bank& newBank, Client& client, unsigned taskId);
    void showTasks() const;

    const Bank& getBank() const;
    const Vector<polymorphic_ptr<Task>>& getTasks() const;
    Vector<polymorphic_ptr<Task>>& getTasks();

};
