# Banking System Project

This project implements a banking system with core functionalities, supporting various user
types such as clients, bank employees, and external firm employees.

## Features

- **Client Operations**: 
  - Check account balance
  - Open and close accounts
  - Redeem checks
  - Change banks
  - List accounts
  - View messages

- **Employee Operations**: 
  - View and handle tasks (open, close, change requests)
  - Approve or disapprove tasks

- **External Firm Operations**: 
  - Send checks to clients

## System Architecture

The system is divided into several classes, each representing a different part of the banking system.
Here's an overview of the key components:

### Key Classes

- **User**: Base class for all user types (Client, Employee, ExternalFirmEmployee)
- **Client**: Inherits from User, represents a bank customer
- **Employee**: Inherits from User, represents a bank employee
- **ExternEmployee**: Inherits from User, represents an external firm employee
- **Bank**: Represents a bank with its accounts and tasks
- **Account**: Represents a bank account
- **Task**: Represents tasks assigned to bank employees
- **Check**: Represents checks issued by external firm employees

![](https://wallpapercave.com/wp/wp4288267.jpg)

## Client Interface

For a user who is a client, the system supports the following interface:

- `check_avl [bank_name] [account_number]` - Displays the balance of the account with number [account_number] in the bank with name [bank_name]. If such an account or bank does not exist, an appropriate error message is displayed.
- `open [bank_name]` - Sends a request to the bank to open a new account. The request automatically includes the client's name, personal ID number, and age (the user does not enter these manually).
- `close [bank_name] [account_number]` - Sends a request to the bank to close the account with number [account_number]. If the data is invalid, an appropriate error message is displayed.
- `redeem [bank_name] [account_number] [verification_code]` - Redeems a check received from a third party through the bank. The money from the check is transferred to the specified account upon verification of the code. If such a check does not exist, an appropriate error message is displayed.
- `change [new_bank_name] [current_bank_name] [account_number]` - Sends a request to the bank to transfer the specified account to another bank.
- `list [bank_name]` - Displays all accounts that the user has in the specified bank.
- `messages` - Shows all messages in chronological order.

## Employee Interface

For a user who is an employee, the system supports the following interface:

- `tasks` - Displays the tasks that need to be completed. Each task has a type, name, and index.
- `view [task_id]` - Shows all details about the task.
- `approve [task_id]` - The employee completes the task and approves the request.
- `disapprove [task_id] [message]` - The employee completes the task and rejects the request.
- `validate [task_id]` - The employee from the new bank sends a request to the old bank, validating whether the user has entered correct data. This validation does not go through an employee of the old bank and is returned immediately. Only Change tasks can be validated.

## ExternEmployee Interface

For a user who is an employee of an external firm, the system supports the following interface:

- `send_check [sum] [verification_code] [egn]` - Creates a check for a user with the specified personal ID number (EGN).

## Common Interface for All Users

All users support the following interface:

- `exit` - Logs out of the profile.
- `whoami` - Displays complete information about the current user.
- `help` - Shows the help menu with supported commands.

