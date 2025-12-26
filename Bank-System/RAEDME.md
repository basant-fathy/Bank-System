# 🏦 Bank System (Project 1)

## Overview
This is a **console-based Bank Management System** developed in C++ to manage client accounts. The system allows performing essential banking operations such as adding new clients, updating client details, deleting clients, finding a client, and viewing all client records. All client data is stored in a text file (`Clients.txt`) to persist data between sessions.

---

## ⚡ Features
- **📋 List All Clients:** Display all clients with account number, PIN code, name, phone number, and balance.
- **➕ Add New Client:** Add clients with unique account numbers.
- **❌ Delete Client:** Remove clients from the system.
- **✏️ Update Client:** Update any client’s details.
- **🔍 Find Client:** Search for a client by account number.
- **🚪 Exit:** Exit the program safely.

---

## 💾 Data Storage
- All client records are stored in `Clients.txt`.
- Each client record is separated by a custom delimiter: `#//#`.
- Deleted records are removed permanently from the file.

---

## 🛠️ Code Structure
- **Structs:** 1 (`stClient`)  
- **Enums:** 1 (`enMainMenueOptions`)  
- **Functions:** 26  

The program uses a vector of `stClient` to handle data in memory and updates the file after every change.

---

## 🏁 How It Works
1. Start the program, and the **Main Menu** appears with six options.
2. User selects an operation (list, add, delete, update, find, exit).
3. Changes are applied to memory and saved to `Clients.txt`.
4. Input validation ensures no duplicate account numbers.

---

## 🌟 Future Improvements
- Adding **transaction history** for each client.
- Implementing **staff authentication**.
- Transition to **OOP design** for scalability.
- Adding a **GUI** interface instead of console-based interaction.

  ___

  ## 📺 Demo Video / LinkedIn Post: 
 - [Watch on LinkedIn](https://www.linkedin.com/posts/bassant-fathy-575582388_%D8%A5%D9%86%D8%AC%D8%A7%D8%B2-%D8%AC%D8%AF%D9%8A%D8%AF-%D8%AE%D8%B7%D9%88%D8%A9-%D8%B9%D9%85%D9%84%D9%8A%D8%A9-%D9%81%D9%8A-%D8%B1%D8%AD%D9%84%D8%A9-%D8%A7%D9%84%D8%A8%D8%B1%D9%85%D8%AC%D8%A9-activity-7405586872594321408-9tk2?utm_source=share&utm_medium=member_desktop&rcm=ACoAAF97FKkBIYwEpy0feW2XgwBRrZ2baraYufs)
