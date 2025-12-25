#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";

enum enMainMenueOptions { List = 1, Add = 2, Delete = 3,
	                      Update = 4, Find = 5, Exit = 6 };

struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

void ShowMainMenue();

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

void PrintAllClientsData(vector <stClient> vClients) {
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

void AddClients(vector <stClient> vClients) {
	char AddMore = 'Y';

	do {
		cout << "Adding New Client:\n\n";

		AddNewClient(vClients);

		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
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

void UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
	stClient Client;
	char Answer;

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

void DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
	stClient Client;
	char Answer;


	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientData(Client);

		cout << "\nAre you sure you want to delete this client? y/n? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";

		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";

	}

}

void FindClientInList(string AccountNumber, vector <stClient>& vClients){
	stClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientData(Client);
	
	else 
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";

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

enMainMenueOptions ReadOption() {
	short c;
	cout << "Choose what do you want to do? [1 to 6]? ";
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

	switch (Option) {
	case enMainMenueOptions::List:
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Add:
		system("cls");
		Header(enMainMenueOptions::Add);
		AddClients(vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Delete:
		system("cls");
		Header(enMainMenueOptions::Delete);
		DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Update:
		system("cls");
		Header(enMainMenueOptions::Update);
		UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Find:
		system("cls");
		Header(enMainMenueOptions::Find);
		FindClientInList(ReadClientAccountNumber(), vClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Exit:
		system("cls");
		Header(enMainMenueOptions::Exit);
		break;
	}
}

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
	cout << "\t[6] Exit.\n";							
	cout << "===========================================\n";
	WhatToDo(ReadOption());
}

int main() {
	ShowMainMenue();

	return 0;
}