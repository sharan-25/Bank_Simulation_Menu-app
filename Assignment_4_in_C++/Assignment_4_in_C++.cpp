#include <iostream>
using namespace std;

/*
We can use class instead of struct if we want too then put struct in comment/remove and remove class comment

class BankAccount // Creating a class BankAccount
{
//The public keyword is an access specifier, which specifies that members (attributes and methods) of the class are accessible from outside the class.
public:
    string givenName;
    string familyName;
    int accountNumber = 0;
    double balance = 0;
};
*/

struct BankAccount {
    string givenName;
    string familyName;
    int accountNumber = 0;
    double balance = 0;
};

const int MAX_ACCOUNTS = 100;   // Creating a global constant maximum number of account 
int numberOfAccounts = -1;      // Creating a global varaible which count how many accounts are there in bank but it start with 0
// as we can use it as index position of last added account in the bank



void bankMenu()
{
    cout << "Bank Simulation Menu" << endl;
    cout << "1.  Add a bank account" << endl;
    cout << "2.  Remove a bank account" << endl;
    cout << "3.  Display the information of a particular client's account" << endl;
    cout << "4.  Apply a deposit to a particular account" << endl;
    cout << "5.  Apply a withdrawal from a particular account" << endl;
    cout << "6.  Sort and display the list of clients according to their balance, family name and given name, in ascending or descending order." << endl;
    cout << "7.  Display the average balance value of the accounts" << endl;
    cout << "8.  Display the total balance value of the accounts" << endl;
    cout << "9.  Create an account and insert it at any position of the Array" << endl;
    cout << "10. Displaying all account details" << endl;
    cout << "0.  Exit" << endl;
    cout << "Enter your choice (0-10): ";
}

/*  for int datatype validation and also validating where it positive or not.
    If it is not int or negative then asking user again and again until user entered a positive integer*/
int intRead() 
{
    int data;
    cin >> data;
    while (cin.fail() || cin.peek() != '\n' || data < 0)
    {
        cin.clear();
        cin.ignore(512, '\n');
        cout << "Please enter the positive integer: ";
        cin >> data;
    }
    return data;
}

/*  for double datatype validation and also validating where it positive or not.
    If it is not double or negative then asking user again and again until user entered a positive double*/
double balanceRead()
{
    double data;
    cin >> data;
    while (cin.fail() || cin.peek() != '\n' || data < 0)
    {
        cin.clear();
        cin.ignore(512, '\n');
        cout << "Please enter the positive numerical value: ";
        cin >> data;
    }
    return data;
}

string stringRead() // for string data validation
{
    string str;
    bool inputValid = true;
    while (inputValid)
    {
        cin >> str;
        if (str.empty()) // if string is null then ask user again
        {
            cout << "Please enter the character value only: ";
            inputValid = true;
        }
        else
        {
            bool check = true;
            for (int i = 0; i < str.length(); i++) // Checking every element from string whether it is alphabet or not 
            {
                char c = str[i];
                if (!isalpha(c)) // if element is not alphabet then ask user again and breaking the for loop
                {
                    check = false;
                    cout << "Please enter the character value only: ";
                    break;
                }
            }
            if (check) // if string is not null and it only contains alphabet then it is valid input. And breaking while loop
            {
                inputValid = false;
            }
        }
    }
    return str;
}

void addAccount(BankAccount accounts[]) // for create an account in the bank
{
    if (numberOfAccounts == MAX_ACCOUNTS - 1) // check whether number of accounts is equal to maximum account or not. If yes, then we cannot new account as accounts are max in bank
    {
        cout << "Maximum number of accounts reached." << endl << endl;
        return;
    }
    cout << "Do you want to add account now? Enter 1 if yes, else enter 0: ";
    while(true)
    {
        int confirm = intRead();
        if (confirm == 1)
        {
            numberOfAccounts++; // Increment number of account as we add one account in the bank

            cout << "Enter client's family name: ";
            accounts[numberOfAccounts].familyName = stringRead();

            cout << "Enter client's given name: ";
            accounts[numberOfAccounts].givenName = stringRead();

            cout << "Enter unique account number (between 10000 and 10099): ";
            int accountNo = 0; // storing the account number in accountNo
            bool loop = true;
            bool check = true;
            while (loop)
            {
                accountNo = intRead();
                if (accountNo >= 10000 && accountNo <= 10099) // check whether accountNo is between 10000 and 10099. If not then asking again and again until user enter valid data
                {
                    check = true;
                    for (int i = 0; i <= numberOfAccounts; i++) // check whether accountNo is already exist or not. If yes, then asking user again and again until user enter unique account number
                    {
                        if (accounts[i].accountNumber == accountNo)
                        {
                            check = false;
                            cout << "This account number already exist. So please enter another unique number: ";
                            break;
                        }
                    }
                    if (check) // if accountNo is between 10000 and 10099 and also it is unique then stopping the while loop then storing accountNo
                    {
                        loop = false;
                    }
                }
                else
                {
                    cout << "Please enter unique account number between 10000 and 10099: ";
                    loop = true;
                }

            }

            accounts[numberOfAccounts].accountNumber = accountNo;

            cout << "Enter account balance: $";
            accounts[numberOfAccounts].balance = balanceRead();

            cout << "Bank account added successfully." << endl << endl;
            return;
        }
        else if (confirm == 0)
        {
            cout << endl;
            return;
        }
        else
        {
            cout << "Please enter either 1 or 0: ";
        }
    }
    
}

void removeAccount(BankAccount accounts[]) // for remove an account from the bank
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot remove any account
    {
        cout << "No one has create a bank account in bank yet, so cannot remove any account." << endl << endl;
        return;
    }
    cout << "Enter the account number which you want to remove : ";
    int accountNo = intRead();
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo) // find the position of the given account number in the array
        {
            // shift the remaining accounts back by one in left direction
            for (int j = i; j < numberOfAccounts; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            numberOfAccounts--; // Decrement number of account as we remove one account from bank
            cout << "Bank account removed successfully." << endl << endl;
            return;
        }
    }
    cout << "Error. This account number does not exist in the bank." << endl << endl; 
}

void display(BankAccount accounts[]) // for displaying account detail
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot display any account detail
    {
        cout << "No one has create a bank account in bank yet, so cannot display any account detail." << endl << endl;
        return;
    }
    cout << "Enter the account number whose details you want to display: ";
    int accountNo = intRead();
    
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo) // find the position of the given account number in the array
        {
            cout << "Detail of client whose account number =  " << accounts[i].accountNumber << " is as follows:";
            cout << "Family name: " << accounts[i].familyName << endl;
            cout << "Given name: " << accounts[i].givenName << endl;
            cout << "Total balance: $" << accounts[i].balance << endl << endl;
            return;
        }
    }
    cout << "Error. This account number does not exist in the bank." << endl << endl;
}

void deposit(BankAccount accounts[]) // for deposit in the account
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot deposit in any account
    {
        cout << "No one has create a bank account in bank yet, so cannot deposit in any account." << endl << endl;
        return;
    }
    cout << "Enter the account: ";
    int accountNo = intRead();
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo) // find the position of the given account number in the array
        {
            cout << "Enter the amount that you want to deposit in account: $";
            double deposit = balanceRead();
            accounts[i].balance += deposit; // adding the deposit amount in balance of that account
            cout << "Current Balance = " << accounts[i].balance << endl;
            cout << "Deposit successful" << endl << endl;
            return;
        }
    }
    cout << "Error. Account number does not exist in the bank." << endl << endl;
}
void withdraw(BankAccount accounts[]) // for withdrawal from the account
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot withdrawal from any account
    {
        cout << "No one has create a bank account in bank yet, so cannot withdrawal from any account." << endl << endl;
        return;
    }
    cout << "Enter the account number: ";
    int accountNo = intRead();
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo) // find the position of the given account number in the array
        {
            cout << "Enter the amount that you want to withdrawal from account: ";
            double withdraw = balanceRead();
            if (withdraw <= accounts[i].balance) // checking whether withdrawal account is less than or equal to balance or not
            {
                accounts[i].balance -= withdraw;
                cout << "Current Balance = $" << accounts[i].balance; // subtracting the withdrawal amount in balance of that account
                cout << "Withdrawal successful" << endl << endl;
                return;
            }
            else // if withdrawal amount is greater than balance the showing error message.
            {
                cout << "Balance = $" << accounts[i].balance << endl;
                cout << "Error: Insufficient balance as withdrawal amount is greater than balance." << endl << endl;
                return;
            }
        }
    }
    cout << "Error. Account number does not exist in the bank." << endl << endl;
}

int sortBy(); // declaration of function sortBy

int orderBy(); // declaration of function orderBy

void sortBalance(BankAccount sort[], int order); // declaration of function sortBalance

void sortFamily(BankAccount sort[], int order); // declaration of function sortFamily

void sortGiven(BankAccount sort[], int order); // declaration of function sortGiven

void sort(BankAccount accounts[]) // for sorting of the array
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot do sorting of the account details
    {
        cout << "No one has create a bank account in bank yet, so cannot perform sort on the accounts." << endl << endl;
        return;
    }
    BankAccount sort[MAX_ACCOUNTS]; 
    // creating a new array sort whose datatype is BankAccount which contains 100 elements
    for (int i = 0; i <= numberOfAccounts;i++) // Now making sort and accounts array as same array means all values of accounts array are in sort array
    {
        sort[i] = accounts[i];
    }
    int option = sortBy();
    int order = orderBy();

    if (option == 1)
    {
        sortBalance(sort,order);
    }
    else if (option == 2)
    {
        sortFamily(sort, order);
    }
    else
    {
        sortGiven(sort, order);
    }
}

int sortBy() // asking user on base of what sorting should be done and return int option which will be 1,2 or 3
{
    cout << "Sort by:" << endl;
    cout << "1. Balance" << endl;
    cout << "2. Family Name" << endl;
    cout << "3. Given Name" << endl;
    cout << "Option (1-3): ";
    int option = 0;
    while (true)
    {
        option = intRead();
        if (option == 1 || option == 2 || option == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid option. Enter 1,2 or 3: ";
        }
    }
    return option;
}

int orderBy() // asking user sorting in ascending or descending order and return int order
{
    cout << "\nOrder by:" << endl;
    cout << "1. Ascending Order" << endl;
    cout << "2. Descending Order" << endl;
    cout << "Order (1-2): ";
    int order = 0;
    while (true)
    {
        order = intRead();
        if (order == 1 || order == 2)
        {
            break;
        }
        else
        {
            cout << "Invalid option. Enter 1 for Ascending order or 2 for Descending Order: ";
        }
    }
    return order;
}

void sortBalance(BankAccount sort[], int order) // Sort and display according to balance 
{
    // using selection sort
    for (int i = 0; i < numberOfAccounts; i++)
    {
        for (int j = i + 1; j <= numberOfAccounts; j++)
        {
            if (sort[j].balance < sort[i].balance)
            {
                BankAccount temp = sort[i];
                sort[i] = sort[j];
                sort[j] = temp;
            }
        }
    }
    
    if (order == 1) // Display sort according to balance in ascending order
    {
        cout << "Sort according to balance in ascending order" << endl << endl;
        cout << "Balance\t\tGiven Name\t\tFamily Name" << endl;
        for (int i = 0; i <= numberOfAccounts; i++)
        {
            cout << "$" << sort[i].balance << "\t\t\t" << sort[i].givenName << "\t\t\t" << sort[i].familyName;
        }
    }
    else // Display sort according to balance in descending order
    {
        cout << "Sort according to balance in descending order" << endl << endl;;
        cout << "Balance\t\tGiven Name\t\tFamily Name" << endl;;
        for (int i = numberOfAccounts; i >= 0; i--)
        {
            cout << "$" << sort[i].balance << "\t\t\t" << sort[i].givenName << "\t\t\t" << sort[i].familyName;
        }
    }
    cout << endl;
}

void sortFamily(BankAccount sort[], int order) // Sort and display according to family name
{
    // using bubble sort algorithm
    for (int i = 0; i < numberOfAccounts; i++)
    {
        for (int j = 0; j < numberOfAccounts - i; j++)
        {
            if (sort[j].familyName > sort[i].familyName)
            {
                BankAccount temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }
    if (order == 1) // Display sort according to family name in ascending order
    {
        cout << "Sort according to family name in ascending order" << endl << endl;
        cout << "Family Name\t\tGiven Name\t\tBalance" << endl;;
        for (int i = 0; i <= numberOfAccounts; i++)
        {
            cout << sort[i].familyName << "\t\t\t" << sort[i].givenName << "\t\t\t\t$" << sort[i].balance;
        }
    }
    else // Display sort according to family Name in descending order
    {
        cout << "Sort according to family name in descending order" << endl << endl;
        cout << "Family Name\t\tGiven Name\t\tBalance" << endl;;
        for (int i = numberOfAccounts; i >= 0; i--)
        {
            cout << sort[i].familyName << "\t\t\t" << sort[i].givenName << "\t\t\t\t$" << sort[i].balance;
        }
    }
    cout << endl;
}

void sortGiven(BankAccount sort[], int order) // Sort and display according to given name 
{
    // using bubble sort algorithm
    for (int i = 0; i < numberOfAccounts; i++)
    {
        for (int j = 0; j < numberOfAccounts - i; j++)
        {
            if (sort[j].familyName > sort[i].familyName)
            {
                BankAccount temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }
    if (order == 1) // Display sort according to given name in ascending order
    {
        cout << "Sort according to given name in ascending order" << endl << endl;
        cout << "Given Name\t\tFamily Name\t\tBalance" << endl;
        for (int i = 0; i <= numberOfAccounts; i++)
        {
            cout << sort[i].givenName << "\t\t\t" << sort[i].familyName << "\t\t\t$" << sort[i].balance << endl;
        }
    }
    else // Display sort according to given Name in descending order
    {
        cout << "Sort according to given name in ascending order" << endl << endl;
        cout << "Given Name\t\tFamily Name\t\tBalance" << endl;;
        for (int i = numberOfAccounts; i >= 0; i--)
        {
            cout << sort[i].givenName << "\t\t\t" << sort[i].familyName << "\t\t\t$" << sort[i].balance << endl;
        }
    }
    cout << endl;
}

void average(BankAccount accounts[]) // for calculate average of the all cilents' balance
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot calculate the average of the accounts balance
    {
        cout << "No one has create a bank account in bank yet, so cannot calculate average balance of the accounts." << endl << endl;
        return;
    }
    double average = 0;
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        average += accounts[i].balance; // adding all accounts balances
    }
    average = average / (numberOfAccounts + 1); // dividing average by number of accounts + 1(as number of accounts start from 0)
    cout << "Average of all account balance = $" << average << endl << endl;
}

void totalBalance(BankAccount accounts[]) // for calculate total of the all cilents' balance
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot calculate total of the accounts balance
    {
        cout << "No one has create a bank account in bank yet, so cannot calculate total balance of the accounts." << endl << endl;
        return;
    }
    double totalBalance = 0;
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        totalBalance = +accounts[i].balance;
    }
    cout << "Total Balance in the bank = " << totalBalance << endl << endl;
}

void addAccountAtSpecific(BankAccount accounts[]) // for adding an account at specific position in the array given by user
{
    if (numberOfAccounts == MAX_ACCOUNTS - 1) // if array size is full then we can't add new elements
    {
        cout << "Maximum number of accounts reached." << endl << endl;
        return;
    }

    cout << "Do you add account now? Enter 1 if yes, else enter 0: ";
    while (true)
    {
        int confirm = intRead();
        if (confirm == 1)
        {
            if (numberOfAccounts == -1) // If array is empty then we can't add element on base of position so we call addNumber() function for adding elements from last
            {
                addAccount(accounts);
                return;
            }
            else
            {
                int position = -1;
                cout << "Enter the position element (Index start with 1) where you want to add account: ";

                //Checking whether the enter position is valid or not and if invalid then ask user again and again until user enter the correct position
                while (position <= 0 || position > numberOfAccounts + 2)
                {
                    position = intRead();
                    if (position <= 0 || position > numberOfAccounts + 2)
                    {
                        cout << "Invalid position. So please enter the valid position: ";
                    }
                }
                if (position == numberOfAccounts + 2) // if position = numberOfAccount + 2 then means last position so calling addAccount function as it add account at last position
                {
                    addAccount(accounts);
                }
                else
                {
                    BankAccount add; // Creating new Bankaccount datatype whose name is add
                    cout << "Enter client's family name: ";
                    add.familyName = stringRead();

                    cout << "Enter client's given name: ";
                    add.givenName = stringRead();

                    //Checking whether user has enter the unique account number between 10000 and 10099 if not then ask again and again until he enter valid account number
                    cout << "Enter unique account number (between 10000 and 10099): ";
                    int accountNo = 0; // storing the account number in accountNo
                    bool loop = true;
                    bool check = true;
                    while (loop)
                    {
                        accountNo = intRead();
                        if (accountNo >= 10000 && accountNo <= 10099) // check whether accountNo is between 10000 and 10099. If not then asking again and again until user enter valid data
                        {
                            check = true;
                            for (int i = 0; i <= numberOfAccounts; i++)
                            {
                                if (accounts[i].accountNumber == accountNo) // check whether accountNo is already exist or not. If yes, then asking user again and again until user enter unique account number
                                {
                                    check = false;
                                    cout << "This account number already exist. So please enter another unique number: ";
                                    break;
                                }
                            }
                            if (check) // if accountNo is between 10000 and 10099 and also it is unique then stopping the while loop then storing accountNo
                            {
                                loop = false;
                            }
                        }
                        else
                        {
                            cout << "Please enter unique account number between 10000 and 10099: ";
                            loop = true;
                        }

                    }

                    add.accountNumber = accountNo;

                    cout << "Enter account balance: $";
                    add.balance = balanceRead();

                    for (int i = numberOfAccounts; i >= position - 1; i--)
                    {
                        accounts[i + 1] = accounts[i]; // shift the accounts details by one in right direction
                    }
                    accounts[position - 1] = add; // adding add varaiable in the given position as new account
                    numberOfAccounts++;

                    cout << "Bank account added successfully." << endl << endl;
                }
            }
        }
        else if (confirm == 0)
        {
            cout << endl;
            return;
        }
        else
        {
            cout << "Please enter either 1 or 0: ";
        }
    }
}

void displayDetails(BankAccount accounts[]) // for displaying all the cilents details 
{
    if (numberOfAccounts == -1) // If there is no bank account in bank then we cannot display all accounts details
    {
        cout << "No one has create a bank account in bank yet, so cannot display all accounts details." << endl << endl;
        return;
    }
    cout << endl <<  "All cilent details are as follows:" << endl;
    for (int i = 0; i <= numberOfAccounts; i++)
    {
        cout << "Account Number: " << accounts[i].accountNumber << endl;
        cout << "Client's Family Name: " << accounts[i].familyName << endl;
        cout << "Client's Given Name: " << accounts[i].givenName << endl;
        cout << "Current Balance: $" << accounts[i].balance << endl << endl;
    }
}

int main()
{
    BankAccount accounts[MAX_ACCOUNTS]; // creating an array of datatype BankAccount struct which has MAX_ACCOUNTS(100) elements

    while (true)
    {
        bankMenu();
        int choice = intRead();
        switch (choice)
        {
        case 1:
            addAccount(accounts);
            break;
        case 2:
            removeAccount(accounts);
            break;
        case 3:
            display(accounts);
            break;
        case 4:
            deposit(accounts);
            break;
        case 5:
            withdraw(accounts);
            break;
        case 6:
            sort(accounts);
            break;
        case 7:
            average(accounts);
            break;
        case 8:
            totalBalance(accounts);
            break;
        case 9:
            addAccountAtSpecific(accounts);
            break;
        case 10:
            displayDetails(accounts);
            break;
        case 0:
            cout << "GOODBYE" << endl << endl;
            return 0;
        default:
            cout << "Please enter a valid choice." << endl << endl;
            break;
        }
    }
    return 0;
}