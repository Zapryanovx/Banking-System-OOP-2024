#include <iostream>
#include "BankingSystem.h"
#include "Client.h"
#include "Employee.h"
#include "ExternEmployee.h"
#include "Task.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include <sstream>
#include <fstream>

namespace MAX_SIZE_CONSTS
{
    constexpr size_t MAX_SIZE_COMMAND = 100;
}

User* currentUser = nullptr;
BankingSystem& bankingSystem = BankingSystem::getInstance();

void printEntryHelp();
void entry();
void handleSignup();
void handleLogin();

void searchInEmployees(Bank& bank, size_t sizeOfEmployees, const MyString& EGN, const MyString& password);

void showHelp();

void handleCreateBank();
void handleClientCommands();
void handleEmployeeCommands();
void handleExternEmployeeCommands();

int main() 
{
    printEntryHelp();

    while (true)
    {
        if (!currentUser) 
        {
            entry();
            continue;
        }

        std::system("CLS");
        std::cout << "Welcome, " << currentUser->getFirstName() << " " << currentUser->getLastName() << std::endl;
        if (currentUser->getTypeUser() == UserType::CLIENT)
        {
            handleClientCommands();
        }
        else if (currentUser->getTypeUser() == UserType::EMPLOYEE)
        {
            handleEmployeeCommands();
        }
        else if (currentUser->getTypeUser() == UserType::EXTERN_EMPLOYEE) 
        {
            handleExternEmployeeCommands();
        }
    }
   
}

void printEntryHelp()
{
    std::cout << "Welcome to the Banking System!" << std::endl;
    std::cout << "You are logged out, please select one of the following" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "> signup" << std::endl;
    std::cout << "> login" << std::endl;
    std::cout << "> create_bank" << std::endl;
    std::cout << "> help" << std::endl;
    std::cout << std::endl;
}

void entry()
{

    MyString command;
    std::cout << "> ";
    std::cin >> command;

    if (command == "signup")
    {
        handleSignup();
        return;

    }

    else if (command == "login")
    {
        handleLogin();
        return;

    }

    else if (command == "create_bank")
    {
         handleCreateBank();
         return;
    }

    else if (command == "help")
    {
        showHelp();
        return;
    }

    else
    {
        std::cout << "[ERROR] Invalid command. Please type \"help\" all available commands to be shown." << std::endl;
        return;
    }
}

void handleSignup()
{   
    MyString firstName, lastName, EGN, password, bankName;
    unsigned age, typeUser;

    std::cout << "Enter first name: " << std::endl;
    std::cout << "> ";
    std::cin >> firstName;

    std::cout << "Enter last name: " << std::endl;
    std::cout << "> ";
    std::cin >> lastName;

    std::cout << "Enter EGN: " << std::endl;
    std::cout << "> ";
    std::cin >> EGN;

    std::cout << "Enter age: " << std::endl;
    std::cout << "> ";
    std::cin >> age;
    std::cin.ignore();
    
    std::cout << "Enter password: " << std::endl;
    std::cout << "> ";
    std::cin >> password;

    std::cout << "Enter user type (1: Client, 2: Employee, 3: ExternEmployee): " << std::endl;
    std::cout << "> ";
    std::cin >> typeUser;
    std::cin.ignore();

    if (typeUser == 1)
    {
        MyString address;
        std::cout << "Enter address: " << std::endl;
        std::cout << "> ";
        std::cin >> address;

        try
        {
            bankingSystem.getClient(EGN);
            std::cout << "[ERROR] User already exists. Please start over." << std::endl;
            return;

        }

        catch (std::exception& e)
        {
            Client* client = new Client(firstName, lastName, EGN, age, address, password);
            currentUser = client;
            bankingSystem.addClient(*client);
        }

    }

    else if (typeUser == 2)
    {
        std::cout << "Enter bank name to work in: ";
        std::cout << "> ";
        std::cin >> bankName;

        try 
        {
            Bank& bank = bankingSystem.getBank(bankName);
            Employee* employee = new Employee(firstName, lastName, EGN, age, password, &bank);
            currentUser = employee;
            bank.addEmployee(*employee);
            bankingSystem.addEmployee(*employee);
        }

        catch (...)
        {
            std::cout << "[ERROR] Bank not found. Please start over." << std::endl;
            return;
        }
    }

    else if (typeUser == 3)
    {
        ExternEmployee* externalEmployee = new ExternEmployee(firstName, lastName, EGN, age, password);
        currentUser = externalEmployee;
        bankingSystem.addExternEmployee(*externalEmployee);
    }
    
    else
    {
        std::cout << "[ERROR] Invalid user type. Please start over." << std::endl;
        return;

    }
}
void handleLogin() 
{
    MyString EGN, password;
    std::cout << "Enter EGN: " << std::endl;
    std::cout << "> ";
    std::cin >> EGN;

    std::cout << "Enter Password: " << std::endl;
    std::cout << "> ";
    std::cin >> password;

    try
    {
        currentUser = &bankingSystem.getClient(EGN);
        if (currentUser->validatePassword(password))
        {
            return;
        }
    }
    catch (...) {}

    try
    {
        currentUser = &bankingSystem.getEmployee(EGN);
        if (currentUser->validatePassword(password))
        {
            return;
        }
    }
    catch (...) {}

    try
    {
        currentUser = &bankingSystem.getExternEmployee(EGN);
        if (currentUser->validatePassword(password))
        {
            return;
        }
    }
    catch (...) {}


    std::cout << "[ERROR] User not found or wrong password." << std::endl;
    currentUser = nullptr;
}   
void showHelp()
{
    if (!currentUser)
    {

        std::cout << "Available commands:" << std::endl;
        std::cout << "[Usage]: signup" << std::endl;
        std::cout << "- starts a form to fill in order to sign up" << std::endl;

        std::cout << "[Usage]: login" << std::endl;
        std::cout << "- starts a form to fill in order to log in" << std::endl;

        std::cout << "[Usage]: create_bank" << std::endl;
        std::cout << "- starts a form to fill in order to create a new bank" << std::endl;

        std::cout << "[Usage]: help" << std::endl;
        std::cout << "- prints a list with all available commands to use" << std::endl;

    }
    
    else if (currentUser->getTypeUser() == UserType::CLIENT)
    {
        std::cout << "Available commands for Client:" << std::endl;
        std::cout << "[Usage]: check_avl [bank_name] [account_number]" << std::endl;
        std::cout << "- checks your balance in your account" << std::endl;

        std::cout << "[Usage]: open [bank_name]" << std::endl;
        std::cout << "- opens a new account to your name in a bank by your choice" << std::endl;

        std::cout << "[Usage]: close [bank_name] [account_number]" << std::endl;
        std::cout << "- closes an account to your name in a bank by your choice" << std::endl;

        std::cout << "[Usage]: redeem [bank_name] [account_number] [verification_code]" << std::endl;
        std::cout << "- redeem a cheque in an account by your choice" << std::endl;

        std::cout << "[Usage]: change [new_bank_name] [current_bank_name] [account_number]" << std::endl;
        std::cout << "- transfer an account to your name to a new bank by your choice" << std::endl;

        std::cout << "[Usage]: list [bank_name]" << std::endl;
        std::cout << "- list all accounts to your name in a bank by your choice" << std::endl;

        std::cout << "[Usage]: messages" << std::endl;
        std::cout << "- checks your inbox" << std::endl;

        std::cout << std::endl;
        
        std::cout << "[Usage] exit" << std::endl;
        std::cout << "- log out from the banking system" << std::endl;

        std::cout << "[Usage] whoami" << std::endl;
        std::cout << "- checks your info" << std::endl;

        std::cout << "[Usage] help" << std::endl;
        std::cout << "- list all commands you are available to use" << std::endl;
    }

    else if (currentUser->getTypeUser() == UserType::EMPLOYEE)
    {
        std::cout << "Available commands for Employee:" << std::endl;
        std::cout << "[Usage]: tasks" << std::endl;
        std::cout << "- list all tasks you have to do" << std::endl;

        std::cout << "[Usage]: view [task_id]" << std::endl;
        std::cout << "- checks a specific task in-depth" << std::endl;

        std::cout << "[Usage]: approve [task_id]" << std::endl;
        std::cout << "- approves an event to be able to happen (open/close)" << std::endl;

        std::cout << "[Usage]: disapprove [task_id] [message]" << std::endl;
        std::cout << "- prevents an event from happening" << std::endl;
       
        std::cout << "[Usage]: validate [task_id]" << std::endl;
        std::cout << "- approves an event to be able to happen (change)" << std::endl;

        std::cout << std::endl;

        std::cout << "[Usage] exit" << std::endl;
        std::cout << "- log out from the banking system" << std::endl;

        std::cout << "[Usage] whoami" << std::endl;
        std::cout << "- checks your info" << std::endl;

        std::cout << "[Usage] help" << std::endl;
        std::cout << "- list all commands you are available to use" << std::endl;
    }

    else if (currentUser->getTypeUser() == UserType::EXTERN_EMPLOYEE)
    {
        std::cout << "Available commands for ExternEmployee:" << std::endl;
        std::cout << "[Usage]: send_check [sum] [verification_code] [EGN]" << std::endl;
        std::cout << "- sends a cheque with an ammount to a client by your choice" << std::endl;

        std::cout << std::endl;

        std::cout << "[Usage] exit" << std::endl;
        std::cout << "- log out from the banking system" << std::endl;

        std::cout << "[Usage] whoami" << std::endl;
        std::cout << "- checks your info" << std::endl;

        std::cout << "[Usage] help" << std::endl;
        std::cout << "- list all commands you are available to use" << std::endl;
    }
}
void handleCreateBank()
{
    std::cout << "Please enter a bank name a new bank to be created: " << std::endl;
    std::cout << "> ";

    char input[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
    std::cin.getline(input, MAX_SIZE_CONSTS::MAX_SIZE_COMMAND);
    MyString bankName(input);

    try
    {
        bankingSystem.getBank(bankName);
        std::cout << "[ERROR] Bank already exists. Please start over." << std::endl;

    }

    catch (std::exception& e)
    {
        bankingSystem.addBank(bankName);
    }
  
}

void handleClientCommands()
{
    showHelp();

    while (true)
    {
        std::cout << "Enter a command:" << std::endl;
        std::cout << "> ";

        char commandBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
        std::cin >> commandBuff;
        MyString command(commandBuff);

        if (command == "check_avl")
        {
            char bankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> bankNameBuff;
            MyString bankName(bankNameBuff);
        
            unsigned accountNumber;
            std::cin >> accountNumber;

            try 
            {
                Bank& bank = bankingSystem.getBank(bankName);
                static_cast<Client*>(currentUser)->check_avl(bank, accountNumber);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }

        }
        else if (command == "open")
        {
            char bankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> bankNameBuff;
            MyString bankName(bankNameBuff);

            try
            {
                Bank& bank = bankingSystem.getBank(bankName);
                static_cast<Client*>(currentUser)->open(bank);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }

        }
        else if (command == "close")
        {
            char bankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> bankNameBuff;
            MyString bankName(bankNameBuff);

            unsigned accountNumber;
            std::cin >> accountNumber;

            try
            {
                Bank& bank = bankingSystem.getBank(bankName);
                static_cast<Client*>(currentUser)->close(bank, accountNumber);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
         
        }

        else if (command == "redeem")
        {
            char bankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> bankNameBuff;
            MyString bankName(bankNameBuff);

            unsigned accountNumber;
            std::cin >> accountNumber;

            char verificationCodeBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> verificationCodeBuff;
            MyString verificationCode(verificationCodeBuff);

            try
            {
                Bank& bank = bankingSystem.getBank(bankName);
                static_cast<Client*>(currentUser)->redeem(bank, accountNumber, verificationCode);
            }

            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }

        }

        else if (command == "change")
        {
            char newBankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> newBankNameBuff;
            MyString newBankName(newBankNameBuff);

            char currentBankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> currentBankNameBuff;
            MyString currentBankName(currentBankNameBuff);

            unsigned accountNumber;
            std::cin >> accountNumber;

            try
            {
                Bank& currBank = bankingSystem.getBank(currentBankName);
                Bank& newBank = bankingSystem.getBank(newBankName);
                static_cast<Client*>(currentUser)->change(newBank, currBank, accountNumber);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
          
        }

        else if (command == "list")
        {
            char bankNameBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> bankNameBuff;
            MyString bankName(bankNameBuff);

            try
            {
                Bank& bank = bankingSystem.getBank(bankName);
                static_cast<Client*>(currentUser)->list(bank);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
           
        }

        else if (command == "messages")
        {
            static_cast<Client*>(currentUser)->showMessages();
        }

        else if (command == "exit")
        {
            currentUser = nullptr;
            std::system("CLS");
            printEntryHelp();
            std::cin.ignore();

            return;
        }

        else if (command == "whoami")
        {
            currentUser->printUserInfo();
        }

        else if (command == "help")
        {
            showHelp();
        }
        else 
        {
            std::cout << "[ERROR] Unavailable command." << std::endl;
        }
    }
  
}
void handleEmployeeCommands()
{

    showHelp();

    while (true)
    {
        char commandBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
        std::cin >> commandBuff;
        MyString command(commandBuff);

        if (command == "tasks") 
        {
            static_cast<Employee*>(currentUser)->showTasks();
        }
        
        else if (command == "view")
        {
            unsigned taskId;
            std::cin >> taskId;

            static_cast<Employee*>(currentUser)->viewTask(taskId - 1);
        }

        else if (command == "approve")
        {
            unsigned taskId;
            std::cin >> taskId;
            
            Employee* employee = static_cast<Employee*>(currentUser);
            const Task* task = employee->getTasks()[taskId - 1].get();

            if (task->getType() != TaskType::OPEN && task->getType() != TaskType::CLOSE)
            {
                std::cout << "[ERROR] approve is used only for open/close tasks." << std::endl;         
            }

            else
            {
                Client client = bankingSystem.getClient(task->getEGN());
                employee->approveTask(client, taskId - 1);
            }
        }

        else if (command == "disapprove")
        {
            unsigned taskId;
            std::cin >> taskId;

            char messageBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> messageBuff;
            MyString message(messageBuff);

            Employee* employee = static_cast<Employee*>(currentUser);

            const Task* task = employee->getTasks()[taskId - 1].get();
            Client client = bankingSystem.getClient(task->getEGN());
            employee->disapproveTask(client, taskId - 1, message);

        }

        else if (command == "validate")
        {
            unsigned taskId;
            std::cin >> taskId;

            Employee* employee = static_cast<Employee*>(currentUser);
            const Task* task = employee->getTasks()[taskId - 1].get();
            
            if (task->getType() != TaskType::CHANGE)
            {
                std::cout << "[ERROR] validate is used only for change tasks." << std::endl;
            }

            else
            {
                Bank oldBank = bankingSystem.getBank(static_cast<const ChangeTask*>(task)->getCurrBankName());
                Client client = bankingSystem.getClient(task->getEGN());


                employee->validateTask(oldBank, client, taskId - 1);
            }

        }

        else if (command == "exit")
        {
            currentUser = nullptr;
            std::system("CLS");
            printEntryHelp();
            std::cin.ignore();

            return;
        }

        else if (command == "whoami")
        {
            currentUser->printUserInfo();
        }

        else if (command == "help")
        {
            showHelp();
        }

        else
        {
            std::cout << "[ERROR] Unavailable command." << std::endl;
        }
    }
}

void handleExternEmployeeCommands() 
{

    showHelp();

    while (true)
    {
        char commandBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
        
        std::cout << "Enter a command:" << std::endl;
        std::cout << "> ";
        std::cin >> commandBuff;

        MyString command(commandBuff);

        if (command == "send_check") 
        {
            double ammount;
            std::cin >> ammount;
            std::cin.ignore();

            char uniqueCodeBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> uniqueCodeBuff;
          
            char EGNBuff[MAX_SIZE_CONSTS::MAX_SIZE_COMMAND] = "";
            std::cin >> EGNBuff;

            MyString uniqueCode(uniqueCodeBuff);
            MyString EGN(EGNBuff);
           
            try
            {
                static_cast<ExternEmployee*>(currentUser)->sendCheck(ammount, uniqueCode, EGN, bankingSystem);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
     
        }

        else if (command == "exit")
        {
            currentUser = nullptr;
            std::system("CLS");
            printEntryHelp();
            std::cin.ignore();

            return;
        }

        else if (command == "whoami")
        {
            currentUser->printUserInfo();
        }

        else if (command == "help")
        {
            showHelp();
        }

        else
        {
            std::cout << "[ERROR] Unavailable command." << std::endl;
        }

    }
}
 