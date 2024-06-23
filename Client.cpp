#include "Client.h"
#include "Bank.h"
#include "Task.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include "BankingSystem.h"

void Client::check_avl(const Bank& bank, unsigned accountNumber)
{
    try 
    {
        const Account& account = bank.getAccount(accountNumber);
        std::cout << "[SUCCESS] Balance: " << account.getBalance() << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cout << e.what() << std::endl;
    }
}

void Client::open(Bank& bank)
{
    polymorphic_ptr<Task> task = new OpenTask(firstName, lastName, EGN, age, bank.getBankName());
    
    bank.assignTask(task);

}

void Client::close(Bank& bank, unsigned accountNumber) 
{   
    polymorphic_ptr<Task> task = new CloseTask(firstName, lastName, EGN, age, bank.getBankName(), accountNumber);
    bank.assignTask(task); 
}

void Client::redeem(Bank& bank, unsigned accountNumber, const MyString& verificationCode)
{
    try
    {
        Account& account = bank.getAccount(accountNumber);

        size_t size = cheques.getSize();
        for (int i = 0; i < size; i++)
        {
            if (cheques[i].getUniqueCode() == verificationCode)
            {
                account.addBalance(cheques[i].getAmmount());
                BankingSystem::getInstance().getBank(bank.getBankName())
                                            .getAccount(accountNumber)
                                            .addBalance(cheques[i].getAmmount());

                cheques.popAt(i);
                std::cout << "[SUCCESS] Check redeemed." << std::endl;
                return;
            }
        }
        std::cout << "[ERROR] Invalid verification code." << std::endl;
    }

    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Client::change(Bank& newBank, Bank& currBank, unsigned accountNumber) 
{
    polymorphic_ptr<Task> task = new ChangeTask(firstName, lastName, EGN, age, accountNumber, currBank.getBankName(), newBank.getBankName());
    newBank.assignTask(task);
}

void Client::list(const Bank& bank)
{
    size_t size = bank.getAccounts().getSize();
    if (size == 0)
    {
        std::cout << "You have not got any accounts in " << bank.getBankName() << std::endl;
        return;
    }

    std::cout << "Accounts in " << bank.getBankName() << ":" << std::endl;    
    for (int i = 0; i < size; i++)
    {
        std::cout << "[Account Number]:" << bank.getAccounts()[i].getAccountNumber() << " [Balance]: " << bank.getAccounts()[i].getBalance() << std::endl;
    }
}

void Client::showMessages()
{
    size_t size = messages.getSize();
    if (size == 0)
    {
        std::cout << "Your inbox is empty." << std::endl;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        messages[i].printMessage();
    }
}

const MyString& Client::getAddress() const
{
    return address;
}


void Client::addAccount(const Account& account) 
{
    accounts.pushBack(account);
}


void Client::removeAccount(const Account& account)
{
    size_t size = accounts.getSize();
    for (int i = 0; i < size; i++)
    {
        if (accounts[i].getAccountNumber() == account.getAccountNumber())
        {
            accounts.popAt(i);
            return;
        }
    }
    std::cout << "[ERROR] Account not found." << std::endl;
}

const Vector<Account>& Client::getAccounts() const
{
    return accounts;
}

void Client::receiveMessage(const MyString& message) 
{
    messages.pushBack(Message(message));
}


void  Client::addCheque(const Cheque& cheque)
{
    cheques.pushBack(cheque);
}

void  Client::removeCheque(const Cheque& cheque)
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

const Vector<Cheque>& Client::getCheques() const
{
    return cheques;
}