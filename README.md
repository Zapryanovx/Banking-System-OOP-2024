# Banking-System-OOP-2024

# Banking System Project

This project implements a banking system with core functionalities, supporting various user types such as clients, bank employees, and external firm employees.

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

The system is divided into several classes, each representing a different part of the banking system. Here's an overview of the key components:

### Key Classes

- **User**: Base class for all user types (Client, Employee, ExternalFirmEmployee)
- **Client**: Inherits from User, represents a bank customer
- **Employee**: Inherits from User, represents a bank employee
- **ExternEmployee**: Inherits from User, represents an external firm employee
- **Bank**: Represents a bank with its accounts and tasks
- **Account**: Represents a bank account
- **Task**: Represents tasks assigned to bank employees
- **Check**: Represents checks issued by external firm employees
