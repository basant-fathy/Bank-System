# 🏦 Bank System Extension 2 (Project 3)

## Overview
This is an **advanced version of the Bank Management System** in C++. In addition to all previous features, this version introduces **user management** with authentication and permissions, allowing multiple staff users to manage clients securely.

All client data is stored in `Clients.txt` and user data in `Useres.txt` to ensure persistence.

---

## ⚡ Features
- **📋 List All Clients:** Display all clients with full details.
- **➕ Add New Client:** Add clients with unique account numbers.
- **❌ Delete Client:** Remove clients from the system.
- **✏️ Update Client:** Update client information.
- **🔍 Find Client:** Search for a client by account number.
- **💵 Transactions:** Deposit, withdraw, and view total balances.
- **👥 User Management:** Add, update, delete, find, and list system users with permissions.
- **🚪 Logout / Exit:** Safely logout or exit the program.

---

## 💾 Data Storage
- **Clients:** Stored in `Clients.txt`, with records separated by `#//#`.
- **Users:** Stored in `Useres.txt`, with records separated by `#//#`.
- Deleted clients or users are permanently removed from the files.

---

## 🛠️ Code Structure
- **Structs:** 2 (`stClient`, `stUser`)  
- **Enums:** 3 (`enMainMenueOptions`, `enTranactionsOptions`, `enManageUseresOptions`)  
- **Functions:** 100+  

The program uses **vectors** for storing client and user data in memory and ensures all changes are reflected in the respective files after each operation.

---

## 🏁 How It Works
1. The program starts with a **login screen**, requiring username and password.
2. Access is granted based on **user permissions**.
3. Users can select operations from the **Main Menu**:
   - Client operations (list, add, delete, update, find)
   - Transactions (deposit, withdraw, total balances)
   - User management (list, add, delete, update, find)
4. All operations are validated to prevent invalid inputs or actions without permissions.
5. Changes are immediately saved to the corresponding text files.

---

## 🌟 Future Improvements
- Adding **transaction history logs** for each client.
- Implementing **role-based access control** for more granular permissions.
- Transitioning to a **fully OOP design** for better maintainability and scalability.
- Developing a **GUI version** for enhanced usability.
