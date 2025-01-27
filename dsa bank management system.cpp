#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct Customer
 {
    int customerID;
    string name;
    string phoneNumber;
    string address;
};

struct CustomerNode 
{
    Customer data;
    CustomerNode* next;
};

struct Account 
{
    int accountID;
    string accountHolderName;
    float balance;
};

struct AccountNode
{
    Account account;  
    AccountNode* next;  
};

void addCustomer(CustomerNode*& head)
{
	Customer customer;
    
    string separator = "===========================================";
    
    cout << "\n" << separator << endl;
    cout << "           Add New Customer               " << endl;
    cout << separator << endl;
    
    cout << "Enter Customer ID: ";
    cin >> customer.customerID;
    cin.ignore();
    
    cout << "Enter Full Name: ";
    getline(cin, customer.name);
    
    cout << "Enter Phone Number (e.g., +92 3104002545): ";
    getline(cin, customer.phoneNumber);
    
    cout << "Enter Address: ";
    getline(cin, customer.address);
    
    CustomerNode* newNode = new CustomerNode();
    newNode->data = customer;
    newNode->next = head;
    head = newNode;
    
    ofstream outFile("customers.txt", ios::app);
    
    if (outFile.is_open()) 
	{
        outFile << customer.customerID << endl;
        outFile << customer.name << endl;
        outFile << customer.phoneNumber << endl;
        outFile << customer.address << endl;
        outFile << separator << endl;
        outFile.close();
        
        cout << "\nCustomer added successfully and saved to file!" << endl;
    }
	else
	{
        cout << "Error: Could not open file to save customer data." << endl;
    }

    cout << separator << endl << endl;
}   

void viewCustomerDetailsFromFile(int customerID)
{
    ifstream inFile("customers.txt"); 
    if (!inFile)
    {
        cout << "Error: Could not open file.\n";
        return;
    }
    
    Customer customer;
    bool found = false;
    
 
    while (inFile >> customer.customerID)
    {
        inFile.ignore(); 
        getline(inFile, customer.name);
        getline(inFile, customer.phoneNumber);
        getline(inFile, customer.address);
        

        if (customer.customerID == customerID)
        {
            found = true;
            string separator = "*************************************************"; 
		    cout << "\n" << separator << endl;
		    cout << "               Customer Details                 \n";
		    cout << separator << endl;
		    cout << "Customer ID:     " << customer.customerID << endl;
		    cout << "Name:            " << customer.name << endl;
		    cout << "Phone Number:    " << customer.phoneNumber << endl;
		    cout << "Address:         " << customer.address << endl;
            cout << separator << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Customer with ID " << customerID << " not found.\n";
    }

    inFile.close(); 
}
void updateCustomerInfoInFile(int customerID)
{
    ifstream inFile("customers.txt");
    if (!inFile)
	{
        cout << "Error: Could not open file.\n";
        return;
    }

    stringstream fileContent;
    Customer customer;
    bool found = false;

    string separator = "===========================================";
    
    while (inFile >> customer.customerID) 
	{
        inFile.ignore(); 
        getline(inFile, customer.name);
        getline(inFile, customer.phoneNumber);
        getline(inFile, customer.address);

        if (customer.customerID == customerID)
	    {
            found = true;
            
    
            cout << "\n" << separator << endl;
            cout << "        Previous Customer Details        " << endl;
            cout << separator << endl;
            cout << "Customer ID: " << customer.customerID << endl;
            cout << "Name: " << customer.name << endl;
            cout << "Phone Number: " << customer.phoneNumber << endl;
            cout << "Address: " << customer.address << endl;
            cout << separator << endl;
            
            cout << "\nCustomer found. Enter new details:\n";
            cout << "Enter new name: ";
            getline(cin, customer.name);
            cout << "Enter new phone number: ";
            getline(cin, customer.phoneNumber);
            cout << "Enter new address: ";
            getline(cin, customer.address);
            

            cout << "\n" << separator << endl;
            cout << "        Updated Customer Details        " << endl;
            cout << separator << endl;
            cout << "Customer ID: " << customer.customerID << endl;
            cout << "Name: " << customer.name << endl;
            cout << "Phone Number: " << customer.phoneNumber << endl;
            cout << "Address: " << customer.address << endl;
            cout << separator << endl;
        }

        fileContent << customer.customerID << endl;
        fileContent << customer.name << endl;
        fileContent << customer.phoneNumber << endl;
        fileContent << customer.address << endl;
        fileContent << "==============================\n";
    }

    inFile.close();

    if (!found) 
	{
        cout << "Customer with ID " << customerID << " not found.\n";
        return;
    }

   
    ofstream outFile("customers.txt");
    if (!outFile) 
	{
        cout << "Error: Could not open file to write.\n";
        return;
    }

    outFile << fileContent.str();
    outFile.close();

    cout << "\nCustomer details updated successfully.\n";
}
void createAccountInFile(AccountNode*& head)
{
    Account newAccount;

    string separator = "===========================================";
    string sectionTitle = "       Create New Account                 ";

    cout << "\n" << separator << endl;
    cout << sectionTitle << endl;
    cout << separator << endl;

    cout << "Enter Account ID: ";
    cin >> newAccount.accountID;
    cin.ignore();

    cout << "Enter Account Holder's Name: ";
    getline(cin, newAccount.accountHolderName);

    cout << "Enter Initial Balance: ";
    cin >> newAccount.balance;

    AccountNode* newNode = new AccountNode;
    newNode->account = newAccount;
    newNode->next = NULL;

    ofstream outFile("accounts.txt", ios::app);
    if (!outFile) 
	{
        cout << "Error: Could not open file to save account data.\n";
        return;
    }

    outFile << newAccount.accountID << endl;
    outFile << newAccount.accountHolderName << endl;
    outFile << newAccount.balance << endl;
    outFile << "==============================\n";

    outFile.close();

    cout << "\n" << separator << endl;
    cout << "       Account Created Successfully!    " << endl;
    cout << separator << endl;
    cout << "Account details have been saved.\n\n";
}



void depositMoneyInFile(AccountNode* head, int accountNumber, float amount) 
{
    AccountNode* current = head;
    bool accountFound = false;

    string separator = "===========================================";
    string sectionTitle = "       Deposit Money                      ";

    cout << "\n" << separator << endl;
    cout << sectionTitle << endl;
    cout << separator << endl;

    while (current != NULL) 
	{
        if (current->account.accountID == accountNumber) 
		{
            current->account.balance += amount;  
            accountFound = true;
            break;
        }
        current = current->next;
    }

    if (!accountFound) 
	{
        cout << "Account with ID " << accountNumber << " not found.\n";
        return;
    }

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) 
	{
        cout << "Error: Could not open the file.\n";
        return;
    }

    string line;
    bool updated = false;
    while (getline(file, line)) 
	{
        int currentAccountID = stoi(line);
        if (currentAccountID == accountNumber) 
		{
            getline(file, line); 
            getline(file, line);  

            file.seekp(file.tellg(), ios::beg);  
            file << currentAccountID << endl;
            file << current->account.accountHolderName << endl;
            file << current->account.balance << endl;
            updated = true;
            break;
        }
    }

    if (updated) 
	{
        cout << "\n" << separator << endl;
        cout << "Deposit Successful!" << endl;
        cout << "New Balance: " << current->account.balance << endl;
        cout << separator << endl;
    } 
	else 
	{
        cout << "Failed to update the account balance.\n";
    }

    file.close();
}

void withdrawMoneyFromFile(AccountNode* head, int accountNumber, float amount) 
{
    AccountNode* current = head;
    bool accountFound = false;

    string separator = "===========================================";
    string sectionTitle = "       Withdraw Money                     ";

    cout << "\n" << separator << endl;
    cout << sectionTitle << endl;
    cout << separator << endl;

    while (current != NULL) 
	{
        if (current->account.accountID == accountNumber) 
		{
            if (current->account.balance >= amount) 
			{
                current->account.balance -= amount;  
                accountFound = true;
            } 
			else 
			{
                cout << "Insufficient funds for withdrawal.\n";
                return;
            }
            break;
        }
        current = current->next;
    }

    if (!accountFound)
	 {
        cout << "Account with ID " << accountNumber << " not found.\n";
        return;
    }

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) 
	{
        cout << "Error: Could not open the file.\n";
        return;
    }

    string line;
    bool updated = false;
    while (getline(file, line)) 
	{
        int currentAccountID = stoi(line);
        if (currentAccountID == accountNumber) 
		{
            getline(file, line); 
            getline(file, line);  

            file.seekp(file.tellg(), ios::beg);  
            file << currentAccountID << endl;
            file << current->account.accountHolderName << endl;
            file << current->account.balance << endl;
            updated = true;
            break;
        }
    }

    if (updated)
	 {
        cout << "\n" << separator << endl;
        cout << "Withdrawal Successful!" << endl;
        cout << "New Balance: " << current->account.balance << endl;
        cout << separator << endl;
    } 
	else 
	{
        cout << "Failed to update the account balance.\n";
    }

    file.close();
}


void calculateInterestFromFile(AccountNode* head, int accountNumber)
 {
    AccountNode* current = head;
    bool accountFound = false;
    const float interestRate = 0.05;
    string separator = "===========================================";
    string sectionTitle = "       Calculate Interest                 ";

    cout << "\n" << separator << endl;
    cout << sectionTitle << endl;
    cout << separator << endl;

    while (current != NULL) 
	{
        if (current->account.accountID == accountNumber) 
		{
            float interest = current->account.balance * interestRate;
            current->account.balance += interest;
            accountFound = true;
            break;
        }
        current = current->next;
    }

    if (!accountFound) 
	{
        cout << "Account with ID " << accountNumber << " not found.\n";
        return;
    }

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) 
	{
        cout << "Error: Could not open the file.\n";
        return;
    }

    string line;
    bool updated = false;
    while (getline(file, line)) 
	{
        int currentAccountID = stoi(line);
        if (currentAccountID == accountNumber) 
		{
            getline(file, line);
            getline(file, line);

            file.seekp(file.tellg(), ios::beg);
            file << currentAccountID << endl;
            file << current->account.accountHolderName << endl;
            file << current->account.balance << endl;
            updated = true;
            break;
        }
    }

    if (updated) 
	{
        cout << "\n" << separator << endl;
        cout << "Interest Calculated Successfully!" << endl;
        cout << "New Balance: " << current->account.balance << endl;
        cout << separator << endl;
    } 
	else 
	{
        cout << "Failed to update the account balance.\n";
    }

    file.close();
}

void viewAllAccountsFromFile(AccountNode* head) 
{
    if (head == NULL) 
	{
        cout << "No accounts to display.\n";
        return;
    }

    string separator = "===========================================";
    string sectionTitle = "           View All Accounts               ";

    cout << "\n" << separator << endl;
    cout << sectionTitle << endl;
    cout << separator << endl;

    AccountNode* current = head;
    while (current != NULL) 
	{
        cout << "Account ID: " << current->account.accountID << "\n";
        cout << "Account Holder: " << current->account.accountHolderName << "\n";
        cout << "Balance: " << current->account.balance << "\n\n";
        current = current->next;
    }

    fstream file("accounts.txt", ios::in);
    if (!file) 
	{
        cout << "Error: Could not open the file.\n";
        return;
    }

    cout << separator << endl;
    cout << "Accounts in the File:\n";
    cout << separator << endl;

    string line;
    while (getline(file, line)) 
	{
        int accountID = stoi(line);
        getline(file, line);
        string accountHolderName = line;
        getline(file, line);
        float balance = stof(line);

        cout << "Account ID: " << accountID << "\n";
        cout << "Account Holder: " << accountHolderName << "\n";
        cout << "Balance: " << balance << "\n\n";
    }

    file.close();
}

bool adminLogin() 
{
    string username, password;
    
    string validUsername = "admin";
    string validPassword = "admin123";

    string separator = "===========================================";
    string header = "          Admin Login Panel                ";

    cout << "\n" << separator << endl;
    cout << header << endl;
    cout << separator << endl;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == validUsername && password == validPassword) 
	{
        cout << "\n" << separator << endl;
        cout << "Login successful! Welcome, Admin." << endl;
        cout << separator << endl;
        return true;
    } 
	else 
	{
        cout << "\n" << separator << endl;
        cout << "Invalid username or password. Please try again." << endl;
        cout << separator << endl;
        return false;
    }
}

void showMenu() 
{
    cout << "\n*****************************************\n";
    cout << "         Welcome to the Bank System     \n";
    cout << "*****************************************\n";
    cout << "\nPlease choose an option from the menu below:\n";
    cout << "--------------------------------------------\n";
    cout << "1. Add Customer\n";
    cout << "2. View Customer Details\n";
    cout << "3. Update Customer Information\n";
    cout << "4. Create Account\n";
    cout << "5. Deposit Money\n";
    cout << "6. Withdraw Money\n";
    cout << "7. Calculate Interest\n";
    cout << "8. View All Accounts\n";
    cout << "9. Exit\n";
    cout << "\n--------------------------------------------\n";
    cout << "Enter your choice (1-9): ";
    cout << "\n*****************************************\n";
}

int main() 
{
    CustomerNode* customerHead = NULL;
    AccountNode* accountHead = NULL;

    string separator = "===========================================";
    string title = "            Admin Panel                    ";

    while (true) 
	{
        cout << "\n" << separator << endl;
        cout << title << endl;
        cout << separator << endl;

        if (adminLogin()) 
		{
            int choice;
            do 
			{
                cout << "\n" << separator << endl;
                showMenu();
                cout << separator << endl;
                cout << "Please enter your choice: ";
                cin >> choice;

                switch (choice) 
				{
                    case 1:
                        addCustomer(customerHead);
                        break;
                    case 2:
                        {
                            int customerID;
                            cout << "Enter Customer ID to view details: ";
                            cin >> customerID;
                            viewCustomerDetailsFromFile(customerID);
                        }
                        break;
                    case 3:
                        {
                            int customerID;
                            cout << "Enter Customer ID to update information: ";
                            cin >> customerID;
                            updateCustomerInfoInFile(customerID);
                        }
                        break;
                    case 4:
                        createAccountInFile(accountHead);
                        break;
                    case 5:
                        {
                            int accountNumber;
                            float amount;
                            cout << "Enter Account Number: ";
                            cin >> accountNumber;
                            cout << "Enter Amount to Deposit: ";
                            cin >> amount;
                            depositMoneyInFile(accountHead, accountNumber, amount);
                        }
                        break;
                    case 6:
                        {
                            int accountNumber;
                            float amount;
                            cout << "Enter Account Number: ";
                            cin >> accountNumber;
                            cout << "Enter Amount to Withdraw: ";
                            cin >> amount;
                            withdrawMoneyFromFile(accountHead, accountNumber, amount);
                        }
                        break;
                    case 7:
                        {
                            int accountNumber;
                            cout << "Enter Account Number to calculate interest: ";
                            cin >> accountNumber;
                            calculateInterestFromFile(accountHead, accountNumber);
                        }
                        break;
                    case 8:
                        viewAllAccountsFromFile(accountHead);
                        break;
                    case 9:
                        cout << "\nExiting the system...\n";
                        return 0;
                    default:
                        cout << "\n" << separator << endl;
                        cout << "Invalid choice. Please try again." << endl;
                        cout << separator << endl;
                }
            } 
			while (true);
        } 
		else 
		{
            cout << "\n" << separator << endl;
            cout << "Admin login failed. Please try again." << endl;
            cout << separator << endl;
        }
    }

    return 0;
}





