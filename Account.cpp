#include "Account.h"

unsigned Account::accountCounter = 0;

Account::Account(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& address, const MyString& bank):
	firstName(firstName), lastName(lastName), EGN(EGN), age(age), address(address), bankName(bankName)
{
	accountNumber = accountCounter;
	accountCounter++;
}

const MyString& Account::getFirstName() const
{
	return firstName;
}

const MyString& Account::getLastName() const
{
	return lastName;
}

const MyString& Account::getEGN() const
{
	return EGN;
}

unsigned Account::getAge() const
{
	return age;
}

const MyString& Account::getAddress() const
{
	return address;
}

const MyString& Account::getBankName() const
{
	return bankName;
}

unsigned Account::getAccountNumber() const
{
	return accountNumber;
}

void Account::addBalance(double ammount)
{	
	if (ammount <= 1e-2)
	{
		throw std::invalid_argument("[ERROR] Invalid ammount.");
	}

	balance += ammount;
}

double Account::getBalance() const
{
	return balance;
}

void Account::printAccountData() const
{
	std::cout << "[ACCOUNT DATA]-[ACCOUNT NUMBER " << accountNumber << " ]" << std::endl;
	std::cout << "[1]-[FIRST NAME] " << firstName << std::endl;
	std::cout << "[2]-[LAST NAME] " << lastName << std::endl;
	std::cout << "[3]-[EGN] " << EGN << std::endl;
	std::cout << "[4]-[AGE] " << age << std::endl;
	std::cout << "[5]-[ADDRESS] " << address << std::endl;

	std::cout << std::endl;
	std::cout << "[BALANCE] " << balance << std::endl;
}
