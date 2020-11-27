// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

struct Customer
{
    int id;
    string name;
};

// UI
bool menuView(Customer *&customers, int &currentCustomerPos);
void addCustomerView(Customer *&customers, int &currentCustomerPos);
void displayCustomersView(Customer *customers, int &currentCustomerPos);
void clearConsole();

// Logic
Customer *addCustomer(Customer *customers, int &currentCustomerPos, Customer newCustomer);
Customer *removeCustomer(Customer *customers, int &currentCustomerPos);

int main()
{
    int currentCustomerPos = 0;
    Customer *customers = new Customer[1]; // Reserve dummy storage

    while (menuView(customers, currentCustomerPos))

        // Clear used space in main memory
        delete[](customers);
    customers = nullptr;
}

// ==============================================================================
// UI
// ==============================================================================

bool menuView(Customer *&customers, int &currentCustomerPos)
{
    int input;

    cout << "-----------------------------------------------" << endl;
    cout << "Customer Manager 2000" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "1. Display Customers" << endl;
    cout << "2. Add Customer" << endl;
    cout << "3. Search Customer" << endl;
    cout << "4. End Program" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Your Input: ";
    cin >> input;

    clearConsole();

    switch (input)
    {
    case 1:
        displayCustomersView(customers, currentCustomerPos);
        break;

    case 2:
        addCustomerView(customers, currentCustomerPos);
        break;

    case 3:
        // TODO Search Customer
        break;

    case 4:
        return false;
        break;

    default:
        cout << endl
             << "-> Invalid Input '" << input << "'" << endl;
    }

    return true;
}

void addCustomerView(Customer *&customers, int &currentCustomerPos)
{
    string customerName = "unkown";

    cout << "-----------------------------------------------" << endl;
    cout << "Add Customer" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Customer Name: ";
    cin >> customerName;
    cout << "-----------------------------------------------" << endl;

    Customer newCustomer;
    newCustomer.id = currentCustomerPos + 1;
    newCustomer.name = customerName;

    // Add Customer to Customers
    customers = addCustomer(customers, currentCustomerPos, newCustomer);
}

void displayCustomersView(Customer *customers, int &currentCustomerPos)
{
    string input;

    cout << "-----------------------------------------------" << endl;
    cout << "Your Customers" << endl;
    cout << "-----------------------------------------------" << endl;

    // Check if a Customer exist
    if (currentCustomerPos <= 0)
    {
        cout << "-> No Customer found!" << endl;
        return;
    }

    for (int i = 0; i < currentCustomerPos; i++)
    {
        Customer currentCustomer = customers[i];
        // or Customer currentCustomer = *(customers + i);

        cout << "---------------------" << endl;
        cout << "Customer " << i + 1 << endl;
        cout << "Id: " << currentCustomer.id << endl;
        cout << "Name: '" << currentCustomer.name << "'" << endl;
        cout << "---------------------" << endl
             << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "Plase press a random Key" << endl;
    cin >> input;
    // TODO wait for random key press
}

void clearConsole()
{
    system("CLEAR");
}

// TODO 
void renderPressEnterToContinue()
{
    cout << "Press Enter to Continue\n";
    cin.ignore(10, '\n');
    cin.get();
    clearConsole();
}

// ==============================================================================
// Logic
// ==============================================================================

Customer *addCustomer(Customer *customers, int &currentCustomerPos, Customer newCustomer)
{
    int newCustomerPos = currentCustomerPos + 1;
    Customer *newCustomers = new Customer[newCustomerPos];

    // Copy old Customer Array into new Customer Array
    for (int i = 0; i < currentCustomerPos; i++)
    {
        newCustomers[i] = customers[i];
        // or *(newCustomers + i) = *(customers + i);
    }

    // Release old used Customer Array Main Storage
    delete[](customers);

    // Add new Customer and updated currentCustomerPos
    newCustomers[newCustomerPos - 1] = newCustomer;
    currentCustomerPos = newCustomerPos;

    return newCustomers;
}