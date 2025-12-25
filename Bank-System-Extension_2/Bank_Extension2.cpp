#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UseresFileName = "Useres.txt";

struct stUser {
	string UserName;
	string PassWord;
	short Permissions;
	bool MarkForDelete_u = false;

};
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enMainMenueOptions {
	List = 1, Add = 2, Delete = 3,
	Update = 4, Find = 5, Transactions = 6, MangeUseres = 7, Exit = 8};
enum enTranactionsOptions { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4 };
enum enManageUseresOptions { ListUseres = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, uMainMenue = 6 };

stUser CurrentUser;

void ShowMainMenue();
void ShowTransactionMainMenue();
void ShowMangeUsersMenueScreen();
void GoBackToMainMenue();
void Login();

const short CAN_VIEW = 1 << 0;  
const short CAN_ADD = 1 << 1;   
const short CAN_DELETE = 1 << 2;
const short CAN_APDATE= 1 << 3;
const short CAN_FIND = 1 << 4;
const short CAN_TRANSACTIONS = 1 << 5;
const short CAN_MANAGE_USERES = 1 << 6;

bool HasPermission(short userPermissions, int requiredPermission) {
	return (userPermissions & requiredPermission) != 0;
}

void Header(enMainMenueOptions Option) {
	switch (Option) {
	case enMainMenueOptions::Add:
		cout << "===========================================\n";
		cout << "\t\tAdd New Client Screen\n";
		cout << "===========================================\n";
		break;
	case enMainMenueOptions::Delete:
		cout << "===========================================\n";
		cout << "\t\tDelet Client Screen\n";
		cout << "===========================================\n";
		break;
	case enMainMenueOptions::Update:
		cout << "===========================================\n";
		cout << "\t\tUpdate Client Screen\n";
		cout << "===========================================\n";
		break;
	case enMainMenueOptions::Find:
		cout << "===========================================\n";
		cout << "\t\tFind Client Screen\n";
		cout << "===========================================\n";
		break;
	case enMainMenueOptions::Exit:
		cout << "===========================================\n";
		cout << "\t\tProgram Ends :-)\n";
		cout << "===========================================\n";
		system("pause>0");
		break;
	}
}
void Header_Transactoin(enTranactionsOptions Option) {
	switch (Option) {
	case enTranactionsOptions::Deposit:
		cout << "===========================================\n";
		cout << "\t\tDeposit Screen\n";
		cout << "===========================================\n";
		break;
	case enTranactionsOptions::Withdraw:
		cout << "===========================================\n";
		cout << "\t\tWithdraw Screen\n";
		cout << "===========================================\n";
		break;
	}
}
void LoginScreen_Header() {
	cout << "-------------------------------------------\n";
	cout << "\t\tLogin Screen\n";
	cout << "-------------------------------------------\n";
}
void Header_Useres(enManageUseresOptions Option) {
	switch (Option) {
	case enManageUseresOptions::AddUser:
		cout << "-------------------------------------------\n";
		cout << "\t\tAdd New Useres Screen\n";
		cout << "-------------------------------------------\n";
		break;
	case enManageUseresOptions::DeleteUser:
		cout << "-------------------------------------------\n";
		cout << "\t\tDelete Useres Screen\n";
		cout << "-------------------------------------------\n";
		break;
	case enManageUseresOptions::UpdateUser:
		cout << "-------------------------------------------\n";
		cout << "\t\tUpdate Useres Screen\n";
		cout << "-------------------------------------------\n";
		break;
	case enManageUseresOptions::FindUser:
		cout << "-------------------------------------------\n";
		cout << "\t\tFind Useres Screen\n";
		cout << "-------------------------------------------\n";
		break;
	}
}
void AccesDeniedScreen() {
	system("cls");
	cout << "-------------------------------------------\n";
	cout << "\nAccess Denied,\n" << "You don't have permission to this action.\n"
		<< "Please Conact Your Admin.\n";
	cout << "-------------------------------------------\n";
	GoBackToMainMenue();
}


vector <string> SplitString(string S1, string delim) {

	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos) {
		sWord = S1.substr(0, pos);

		if (sWord != "")
			vString.push_back(sWord);

		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
		vString.push_back(S1);

	return vString;

}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#") {
	string ClientRecord = "";

	ClientRecord += Client.AccountNumber + Seperator;
	ClientRecord += Client.PinCode + Seperator;
	ClientRecord += Client.Name + Seperator;
	ClientRecord += Client.Phone + Seperator;
	ClientRecord += to_string(Client.AccountBalance);

	return ClientRecord;
}

stClient ConvertLinetoRecord(string LineData, string Seperator = "#//#") {
	stClient Client;

	vector<string> vClientData;
	vClientData = SplitString(LineData, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

vector <stClient> LoadClientsDataFromFile(string FileName) {
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

stUser ConvertLinetoRecord_Useres(string LineData, string Seperator = "#//#") {
	stUser User;

	vector<string> vUserData;
	vUserData = SplitString(LineData, Seperator);

	User.UserName = vUserData[0];
	User.PassWord = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}

vector <stUser> LoadClientsDataFromFile_Useres(string FileName) {
	vector <stUser> vUser;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stUser User;

		while (getline(MyFile, Line)) {
			User = ConvertLinetoRecord_Useres(Line);
			vUser.push_back(User);
		}
		MyFile.close();
	}
	return vUser;
}

void PrintClientData(stClient Client) {
	cout << "\n\nThe following is the extracted client details:\n";
	cout << "------------------------------------------------\n";
	cout << "\nAccountNumber : " << Client.AccountNumber;
	cout << "\nPinCode       : " << Client.PinCode;
	cout << "\nName          : " << Client.Name;
	cout << "\nPhone         : " << Client.Phone;
	cout << "\nAccountBalance: " << Client.AccountBalance;
	cout << "\n------------------------------------------------\n";
}

void PrintClientRecord(stClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client) {

	for (stClient C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}

stClient ReadNewClintData(vector <stClient> vClients) {
	stClient ClientData;

	cout << "Enter Account Number? ";
	getline(cin >> ws, ClientData.AccountNumber);

	if (FindClientByAccountNumber(ClientData.AccountNumber, vClients, ClientData)) {
		do {
			cout << "\nClient with [" << ClientData.AccountNumber << "] "
				<< "already exists, Enter anther Account Number? ";
			getline(cin >> ws, ClientData.AccountNumber);
		} while (FindClientByAccountNumber(ClientData.AccountNumber, vClients, ClientData));
	}

	cout << "Enter PinCode? ";
	getline(cin, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin, ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin, ClientData.Phone);

	cout << "Enter AccountBalance? ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

void AddDataLineToFile(string FileName, string stDataline) {

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << stDataline << endl;

		MyFile.close();
	}
}

void AddNewClient(vector <stClient> vClients) {
	stClient ClientData;
	ClientData = ReadNewClintData(vClients);
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(ClientData));
}

string ReadClientAccountNumber() {
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	} return false;
}

void SaveCleintsDataToFile(string FileName, vector<stClient> vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);
	string DataLine;

	if (MyFile.is_open()) {

		for (stClient C : vClients) {

			if (C.MarkForDelete == false) {
				//we only write records that are not marked for delete.      
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

stClient ChangeClientRecord(string AccountNumber) {

	stClient ClientData;

	ClientData.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin >> ws, ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin >> ws, ClientData.Phone);

	cout << "Enter AccountBalance? ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

void PrintAllClientsData(vector <stClient> vClients) {

	if (!HasPermission(CurrentUser.Permissions, CAN_VIEW)) {
		AccesDeniedScreen();
		return;
	}
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;

	for (stClient Client : vClients) {
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
}

void AddClients() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	char AddMore = 'Y';

	if (!HasPermission(CurrentUser.Permissions, CAN_ADD)) {
		AccesDeniedScreen();
		return;
	}

	Header(enMainMenueOptions::Add);

	do {
		cout << "Adding New Client:\n\n";

		AddNewClient(vClients);

		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

void UpdateClientByAccountNumber() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	stClient Client;
	char Answer;

	if (!HasPermission(CurrentUser.Permissions, CAN_APDATE)) {
		AccesDeniedScreen();
		return;
	}

	Header(enMainMenueOptions::Update);
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientData(Client);

		cout << "\nAre you sure you want to update this client? y/n? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {

			for (stClient& C : vClients) {

				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Update Successfully.\n";
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!\n";
	}
}

void DeleteClientByAccountNumber() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	char Answer;

	if (!HasPermission(CurrentUser.Permissions, CAN_DELETE)) {
		AccesDeniedScreen();
		return;
	}

	Header(enMainMenueOptions::Delete);

	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientData(Client);

		cout << "\nAre you sure you want to delete this client? y/n? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.\n";
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!\n";
	}
}

void FindClientInList() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;

	if (!HasPermission(CurrentUser.Permissions, CAN_FIND)) {
		AccesDeniedScreen();
		return;
	}

	Header(enMainMenueOptions::Find);
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientData(Client);

	else
		cout << "\nClient with Account Number (" << AccountNumber
		<< ") is Not Found!";
}

enMainMenueOptions ReadOption() {
	short c;
	cout << "Choose what do you want to do? [1 to 8]? ";
	cin >> c;

	return (enMainMenueOptions)c;

}

void GoBackToMainMenue() {
	cout << "\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void WhatToDo(enMainMenueOptions Option) {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	switch (Option) {
	case enMainMenueOptions::List:
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Add:
		system("cls");
		AddClients();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Delete:
		system("cls");
		DeleteClientByAccountNumber();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Update:
		system("cls");
		UpdateClientByAccountNumber();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Find:
		system("cls");
		FindClientInList();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionMainMenue();
		break;
	case enMainMenueOptions::MangeUseres:
		system("cls");
		ShowMangeUsersMenueScreen();
		break;
	case enMainMenueOptions::Exit:
		system("cls");
		Login();
		break;
	}
}

//Extension1 - Transactions 

double SumBalances(vector <stClient> vClients) {
	double Sum = 0;
	for (stClient& C : vClients) {
		Sum += C.AccountBalance;
	}
	return Sum;
}

void PrintClientRecordInBalancesList(stClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintBalancesList(vector <stClient> vClients) {
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;

	for (stClient Client : vClients) {
		PrintClientRecordInBalancesList(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;

	cout << "\n\t\t\t\t\tTotalBalances = " << SumBalances(vClients) << endl;

}

void GoBackToTransactionMainMenue() {
	cout << "\nPress any key to go back to Transactions Main Menue...";
	system("pause>0");
	ShowTransactionMainMenue();
}

double ReadAmount(enTranactionsOptions Option) {
	double Amount;
	if (Option == enTranactionsOptions::Deposit)
		cout << "\nPlease enter deposit amount? ";
	else
		cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;
	return Amount;
}

bool DepositeBlanceByAccountNumber(string AccountNumber, double DepositeAmount, vector <stClient>& vClients) {
	char Answer;
	short Counter = 0;

	cout << "\nAre you sure you want to preform this transaction? y/n? ";
	cin >> Answer;

	if (tolower(Answer) == 'y') {
		for (stClient& C : vClients) {

			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += DepositeAmount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully, New Balance is: "
					<< C.AccountBalance << endl;
				return true;
			}
		}
		return true;
	}
}

void DepositScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	double Amount;
	Header_Transactoin(enTranactionsOptions::Deposit);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
	}

	PrintClientData(Client);
	Amount = ReadAmount(enTranactionsOptions::Deposit);

	DepositeBlanceByAccountNumber(AccountNumber, Amount, vClients);
}

void WithdrawScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	double Amount;

	Header_Transactoin(enTranactionsOptions::Withdraw);

	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
	}

	PrintClientData(Client);

	Amount = ReadAmount(enTranactionsOptions::Withdraw);

	while (Amount > Client.AccountBalance) {
		cout << "\nAmont Exceeds the balance, "
			<< "you can withdraw up to : "
			<< Client.AccountBalance;
		Amount = ReadAmount(enTranactionsOptions::Withdraw);
	}

	DepositeBlanceByAccountNumber(AccountNumber, Amount * -1, vClients);
}

enTranactionsOptions ReadTransationOption() {
	short c;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> c;

	return (enTranactionsOptions)c;

}

void WhatToDo_Transation(enTranactionsOptions Option) {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	switch (Option) {
	case enTranactionsOptions::Deposit:
		system("cls");
		DepositScreen();
		GoBackToTransactionMainMenue();
		break;
	case enTranactionsOptions::Withdraw:
		system("cls");
		WithdrawScreen();
		GoBackToTransactionMainMenue();
		break;
	case enTranactionsOptions::TotalBalances:
		system("cls");
		PrintBalancesList(vClients);
		GoBackToTransactionMainMenue();
		break;
	case enTranactionsOptions::MainMenue:
		ShowMainMenue();
		break;
	}
}

void ShowTransactionMainMenue() {
	if (!HasPermission(CurrentUser.Permissions, CAN_TRANSACTIONS)) {
		AccesDeniedScreen();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";
	WhatToDo_Transation(ReadTransationOption());
}

//Extension2 - Manage Useres

string ReadUsername() {
	string Username = "";
	cout << "\nPlease enter Username? ";
	cin >> Username;
	return Username;
}

string ReadUserPassword() {
	string Password = "";
	cout << "Please enter Password? ";
	cin >> Password;
	return Password;
}

short ReadPermissions(stUser User)
{
	short Permission = 0;
	char YesNo;

	cout << "\nDo you want to give full access? (y/n): ";
	cin >> ws >> YesNo;

	if (tolower(YesNo) == 'y')
		return -1;


	cout << "\nDo you want to give access to:\n";

	cout << "Show Clients List? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_VIEW;

	cout << "Add Client? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_ADD;

	cout << "Delete Client? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_DELETE;

	cout << "Update Client? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_APDATE;

	cout << "Find Client? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_FIND;

	cout << "Transactions? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_TRANSACTIONS;

	cout << "Manage Users? (y/n): ";
	cin >> ws >> YesNo;
	if (tolower(YesNo) == 'y')
		Permission |= CAN_MANAGE_USERES;

	return Permission;
}

bool FindUserByUsername(string Username, vector <stUser> vUser, stUser& User) {
	for (stUser u : vUser) {
		if (u.UserName == Username) {
			User = u;
			return true;
		}
	}
	return false;
}

bool FindUserByUsernameAndPasswosd(string Username, string Password, vector <stUser> vUseres, stUser& User) {
	for (stUser C : vUseres) {
		if (C.UserName == Username && C.PassWord == Password) {
			User = C;
			return true;
		}
	}
	return false;
}

void GoBackToMangeMenue() {
	cout << "\nPress any key to go back to Manage Users Menue Screen...";
	system("pause>0");
	ShowMangeUsersMenueScreen();
}

void PrintUserRecordInUsereslistList(stUser User) {
	cout << "| " << setw(20) << left << User.UserName;
	cout << "| " << setw(12) << left << User.PassWord;
	cout << "| " << setw(12) << left << User.Permissions;
}

void PrintUserData(stUser User) {
	cout << "\n\nThe following is the extracted User details:\n";
	cout << "------------------------------------------------\n";
	cout << "\nUsername   : " << User.UserName;
	cout << "\nPassword   : " <<User.PassWord;
	cout << "\nPermission : " << User.Permissions;	
	cout << "\n------------------------------------------------\n";
}

stUser ReadNewUser(vector <stUser> vUser) {
	stUser User;

	cout << "Enter Username: ";
	getline(cin >> ws, User.UserName);

	if (FindUserByUsername(User.UserName, vUser, User)) {
		do {
			cout << "\nUser with [" << User.UserName << "] "
				<< "already exists, Enter anther Username? ";
			getline(cin >> ws, User.UserName);

		} while (FindUserByUsername(User.UserName, vUser, User));
	}

	cout << "Enter Password: ";
	getline(cin >> ws, User.PassWord);

	User.Permissions = ReadPermissions(User);

	return User;
}

string ConvertRecordToLine_Useres(stUser User, string Seperator = "#//#") {
	string UserRecord = "";

	UserRecord += User.UserName + Seperator;
	UserRecord += User.PassWord + Seperator;
	UserRecord += to_string(User.Permissions);

	return UserRecord;
}

void AddNewUser(vector <stUser> vUser) {
	stUser User;
	User = ReadNewUser(vUser);
	AddDataLineToFile(UseresFileName, ConvertRecordToLine_Useres(User));
}

bool MarkUserForDeleteByUsername(string Username, vector <stUser>& vUser) {
	for (stUser& u : vUser) {
		if (u.UserName == Username) {
			u.MarkForDelete_u = true;
			return true;
		}
	} return false;
}

void SaveUseresDataToFile(string FileName, vector<stUser> vUser) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);
	string DataLine;

	if (MyFile.is_open()) {

		for (stUser U : vUser) {

			if (U.MarkForDelete_u == false) {
				//we only write records that are not marked for delete.      
				DataLine = ConvertRecordToLine_Useres(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

stUser ChangeUserRecord(string Username) {

	stUser User;

	User.UserName = Username;

	cout << "\n\nEnter passwoer? ";
	getline(cin >> ws, User.PassWord);

	User.Permissions = ReadPermissions(User);

	return User;
}

void PrintUseresList(vector <stUser> vUseres) {
	cout << "\n\t\t\t\t\tUseres List (" << vUseres.size() << ") User(s).";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(12) << "Password";
	cout << "| " << left << setw(12) << "Permissions";
	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
	for (stUser u : vUseres) {
		PrintUserRecordInUsereslistList(u);
		cout << endl;
	}

	cout << "\n_______________________________________________________"
		<< "_________________________________________\n" << endl;
}

void AddUseres() {
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	char AddMore = 'Y';
	Header_Useres(enManageUseresOptions::AddUser);
	do {
		cout << "Adding New User:\n\n";

		AddNewUser(vUser);

		cout << "\nUser Added Successfully, do you want to add more Useres? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

void UpdateUserByUsername() {
	stUser User;
	char Answer;
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	Header_Useres(enManageUseresOptions::UpdateUser);

	string Username = ReadUsername();

	if (FindUserByUsername(Username, vUser, User)) {

		PrintUserData(User);

		cout << "\nAre you sure you want to update this user? y/n? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {

			for (stUser& U : vUser) {

				if (U.UserName == Username) {
					U = ChangeUserRecord(Username);
					break;
				}
			}

			SaveUseresDataToFile(UseresFileName, vUser);

			cout << "\n\nUser Updated Successfully.\n";

		}
	}
	else {
		cout << "\nUser with Username (" << Username
			<< ") is Not Found!\n";
	}
}

void DeleteUserByUsername() {
	stUser User;
	char Answer;
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	Header_Useres(enManageUseresOptions::DeleteUser);

	string Username = ReadUsername();

	if (Username == "Admin") {
		cout << "\nYou cannot delete this user!\n";
		return;
	}
	if (FindUserByUsername (Username, vUser, User)) {

		PrintUserData(User);

		cout << "\nAre you sure you want to delete this user? y/n? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			MarkUserForDeleteByUsername(Username, vUser);
			SaveUseresDataToFile(UseresFileName, vUser);

			vUser = LoadClientsDataFromFile_Useres(UseresFileName);

			cout << "\n\nUser Deleted Successfully.\n";

		}
	}
	else {
		cout << "\nUser with username (" << Username
			<< ") is Not Found!";
	}
}

void FindUserInList() {
	stUser User;
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	Header_Useres(enManageUseresOptions::FindUser);

	string Username = ReadUsername();

	if (FindUserByUsername(Username, vUser, User)) 
		PrintUserData(User);

	else
		cout << "\nUser with Username (" << Username
		<< ") is Not Found!\n";
}

enManageUseresOptions ReadManageUseresOption() {
	short c;
	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> c;

	return (enManageUseresOptions)c;

}

void WhatToDo_ManageUseres(enManageUseresOptions Option) {
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	switch (Option) {
	case enManageUseresOptions::ListUseres:
		system("cls");
		PrintUseresList(vUser);
		GoBackToMangeMenue();
		break;
	case enManageUseresOptions::AddUser:
		system("cls");
		AddUseres();
		GoBackToMangeMenue();
		break;
	case enManageUseresOptions::DeleteUser:
		system("cls");
		DeleteUserByUsername();
		GoBackToMangeMenue();
		break;
	case enManageUseresOptions::UpdateUser:
		system("cls");
		UpdateUserByUsername();
		GoBackToMangeMenue();
		break;
	case enManageUseresOptions::FindUser:
		system("cls");
		FindUserInList();
		GoBackToMangeMenue();
		break;
	case enManageUseresOptions::uMainMenue:
		ShowMainMenue();
		break;
	}
}

void ShowMangeUsersMenueScreen() {
	if (!HasPermission(CurrentUser.Permissions, CAN_MANAGE_USERES)) {
		AccesDeniedScreen();
		return;
	}
	system("cls");
	cout << "===========================================\n";
	cout << "\t  Mange Users Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================\n";
	WhatToDo_ManageUseres(ReadManageUseresOption());
}

//Main

void ShowMainMenue() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Tranactions.\n";
	cout << "\t[7] Manage Useres.\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";
	WhatToDo(ReadOption());
}

void Login() {
	vector <stUser> vUser = LoadClientsDataFromFile_Useres(UseresFileName);

	stUser User;
	string Username;
	string Password;

	LoginScreen_Header();
	
	do {
		Username = ReadUsername();
		Password = ReadUserPassword();
		if (!FindUserByUsernameAndPasswosd(Username, Password, vUser, CurrentUser)) {
			system("cls");
			LoginScreen_Header();
			cout << "\nInvlaid Username/Password!\n";
		}

	} while (!FindUserByUsernameAndPasswosd(Username, Password, vUser, CurrentUser));

	ShowMainMenue();
}

int main() {
	Login();
	return 0;
}