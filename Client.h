#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Account.h"
#include "User.h"
#include "Message.h"
#include "Cheque.h"

class Bank;
class Client : public User
{
private:
    MyString address;
    Vector<Cheque> cheques;
    Vector<Message> messages;
    Vector<Account> accounts;

public:
    Client() = default;
    Client(const MyString& firstName, const MyString& lastName, const MyString& EGN, int age, const MyString& address, const MyString& password)
        : User(firstName, lastName, EGN, age, password, UserType::CLIENT) {}

    void check_avl(const Bank& bank, unsigned accountNumber);
    void open(Bank& bank);
    void close(Bank& bank, unsigned accountNumber);
    void redeem(Bank& bank, unsigned accountNumber, const MyString& verificationCode);
    void change(Bank& newBank, Bank& currBank, unsigned accountNumber);
    void list(const Bank& bank);
    void showMessages();

    const MyString& getAddress() const;
    void addAccount(const Account& account);
    void removeAccount(const Account& account);
    const Vector<Account>& getAccounts() const;

    void addCheque(const Cheque& cheque);
    void removeCheque(const Cheque& cheque);
    const Vector<Cheque>& getCheques() const;


    void receiveMessage(const MyString& message);
};
