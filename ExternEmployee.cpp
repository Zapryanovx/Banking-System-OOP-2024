#include "ExternEmployee.h"
#include "BankingSystem.h"
#include "Client.h"

bool ExternEmployee::isAlnum(const MyString& uniqueCode) const
{
    size_t size = uniqueCode.getLength();
    for (int i = 0; i < size; i++)
    {
        char c = uniqueCode[i];
        if (!((c >= '0' && c <= '9')
            || (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')))
        {
            return false;
        }
    }
    return true;
}

bool ExternEmployee::isCodeUnique(const BankingSystem& bankingSystem, const MyString& uniqueCode) const
{
    try
    {
        bankingSystem.getCheque(uniqueCode);
        return false;
    }
    catch (std::exception&)
    {
        return true;
    }
}

bool ExternEmployee::isUniqueCodeValid(const BankingSystem& bankingSystem, const MyString& uniqueCode) const
{
    if (uniqueCode.getLength() != 3)
    {
        std::cout << "[ERROR] Verification code must be exactly 3 characters long." << std::endl;
        return false;
    }

    if (!isAlnum(uniqueCode))
    {
        std::cout << "[ERROR] Verification code must be alphanumeric." << std::endl;
        return false;
    }

    if (!isCodeUnique(bankingSystem, uniqueCode))
    {
        std::cout << "[ERROR] Verification code must be unique." << std::endl;
        return false;
    }

    return true;
}

void ExternEmployee::sendCheck(double amount, const MyString& uniqueCode, const MyString& EGN, BankingSystem& bankingSystem) const
{
    if (!isUniqueCodeValid(bankingSystem, uniqueCode))
    {
        std::cout << "[ERROR] Invalid verification code." << std::endl;
        return;
    }

    if (amount < 0.01)
    {
        std::cout << "[ERROR] Invalid amount." << std::endl;
        return;
    }

    try
    {
        Client& client = bankingSystem.getClient(EGN);
        Cheque cheque(uniqueCode, amount);
        bankingSystem.addCheque(cheque);
        client.addCheque(cheque);  
        std::cout << "[SUCCESS] Check sent to client with EGN: " << EGN << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
