# 🏦 Bank System Extension (Project 2)

## Overview
This is an **extended version of the Bank Management System** in C++. In addition to basic client operations, this version introduces **bank transactions** including deposits, withdrawals, and total balances.

All client data is stored in a text file (`Clients.txt`) to ensure persistence.

---

## ⚡ Features
- **📋 List All Clients:** Display all clients with full details.
- **➕ Add New Client:** Add clients with unique account numbers.
- **❌ Delete Client:** Remove clients from the system.
- **✏️ Update Client:** Update client information.
- **🔍 Find Client:** Search for a client by account number.
- **💵 Transactions:** Deposit, withdraw, and view total balances.
- **🚪 Exit:** Exit the program safely.

---

## 💾 Data Storage
- Client records are stored in `Clients.txt`.
- Each record uses the delimiter: `#//#`.
- Deleted clients are permanently removed from the file.

---

## 🛠️ Code Structure
- **Structs:** 1 (`stClient`)  
- **Enums:** 2 (`enMainMenueOptions`, `enTranactionsOptions`)  
- **Functions:** 38  

The program maintains client data in a vector and ensures all changes are reflected in the file after each operation.

---

## 🏁 How It Works
1. The program displays the **Main Menu** with seven options.
2. Users select operations (list, add, delete, update, find, transactions, exit).
3. The **Transactions menu** allows deposits, withdrawals, and checking total balances.
4. All actions are validated to avoid invalid operations or duplicate account numbers.

**📺 Demo Video / LinkedIn Post:**  
[Watch how the system works](https://www.linkedin.com/posts/bassant-fathy-575582388_%D8%A5%D9%86%D8%AC%D8%A7%D8%B2-%D8%AC%D8%AF%D9%8A%D8%AF-%D8%AE%D8%B7%D9%88%D8%A9-%D8%B9%D9%85%D9%84%D9%8A%D8%A9-%D9%81%D9%8A-%D8%B1%D8%AD%D9%84%D8%A9-%D8%A7%D9%84%D8%A8%D8%B1%D9%85%D8%AC%D8%A9-activity-7405586872594321408-9tk2?utm_source=share&utm_medium=member_desktop&rcm=ACoAAF97FKkBIYwEpy0feW2XgwBRrZ2baraYufs)

---

## 🌟 Future Improvements
- Adding **transaction history logs** for each client.
- Implementing **staff authentication and access control**.
- Transitioning to a **fully OOP design** for better maintainability.
- Developing a **GUI version** for a more user-friendly interface.
