// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>
#include <string>

using namespace std;

struct Customer
{
    string id;
    string name;
};

struct FoundCustomers
{
    int foundCustomerPos;
    Customer *customers;
};

// UI
bool menuView(Customer *&customers, int &currentCustomerPos);
void addCustomerView(Customer *&customers, int &currentCustomerPos);
void customersView(Customer *customers, int &currentCustomerPos);
void customerView(Customer customer);
void removeCustomerView(Customer *&customers, int &currentCustomerPos);
bool searchCustomerView(Customer *customers, int currentCustomerPos);
void searchCustomerByNameView(Customer *customers, int currentCustomerPos);
void searchCustomerByIdView(Customer *customers, int currentCustomerPos);
void clearConsole();
void pressEnterToContinue();

// Debugging
void outputCustomers(Customer *customers, int currentCustomerPos);
void fillCustomersWithDummyData(Customer *&customers, int &currentCustomerPos);

// Logic
Customer *addCustomer(Customer *customers, int &currentCustomerPos, Customer newCustomer);
Customer *removeCustomer(Customer *customers, int &currentCustomerPos, string id);
FoundCustomers getCustomersByName(Customer *customers, int &currentCustomerPos, string name);
FoundCustomers getCustomersById(Customer *customers, int &currentCustomerPos, string id);
int getCustomerIndexById(Customer *customers, int currentCustomerPos, string id);

int main()
{
    int currentCustomerPos = 0;
    Customer *customers = new Customer[1]; // Reserve dummy storage

    fillCustomersWithDummyData(customers, currentCustomerPos);

    while (menuView(customers, currentCustomerPos))
        ;

    // Clear used space in main memory
    delete[](customers);
    customers = nullptr;

    return 0;
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
    cout << "3. Remove Customer" << endl;
    cout << "4. Search Customer" << endl;
    cout << "5. End Program" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Your Input: ";
    cin >> input;

    clearConsole();

    switch (input)
    {
    case 1:
        customersView(customers, currentCustomerPos);
        break;

    case 2:
        addCustomerView(customers, currentCustomerPos);
        break;

    case 3:
        removeCustomerView(customers, currentCustomerPos);
        break;

    case 4:
        while (searchCustomerView(customers, currentCustomerPos))
            ;
        break;

    case 5:
        return false;

    default:
        cout << endl
             << "-> Invalid Input '" << input << "'" << endl;
    }

    return true;
}

void addCustomerView(Customer *&customers, int &currentCustomerPos)
{
    string name = "unkown";
    string input;

    cout << "-----------------------------------------------" << endl;
    cout << "Add Customer" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Customer Name: ";
    cin >> name;
    cout << "-----------------------------------------------" << endl;

    // Create new Customer
    Customer newCustomer;
    newCustomer.id = to_string(currentCustomerPos + 1);
    newCustomer.name = name;

    clearConsole();
    customerView(newCustomer);
    cout << "Is that correct? (y/n)" << endl;
    cin >> input;

    // Add Customer
    if (input == "y")
    {
        customers = addCustomer(customers, currentCustomerPos, newCustomer);
        clearConsole();
        cout << "-> Sucessfully added Customer" << endl;
        return;
    }

    clearConsole();
    cout << "-> Sucessfully cancled creation of Customer" << endl;
}

void removeCustomerView(Customer *&customers, int &currentCustomerPos)
{
    string input;
    string id;

    cout << "-----------------------------------------------" << endl;
    cout << "Remove Customer" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Customer Id: ";
    cin >> input;
    id = input;
    cout << "-----------------------------------------------" << endl;

    clearConsole();

    // Check if Customer exists
    int index = getCustomerIndexById(customers, currentCustomerPos, id);
    if (index >= 0)
    {
        Customer customerToRemove = customers[index];

        customerView(customerToRemove);
        cout << "Do you really want to remove this Customer? (y/n)" << endl;
        cin >> input;
        clearConsole();

        // Remove Customer
        if (input == "y")
        {
            customers = removeCustomer(customers, currentCustomerPos, id);
            cout << "-> Sucessfully removed Customer by Id '" << id << "'" << endl;
            return;
        }

        cout << "-> Sucessfully cancled deletion of Customer" << endl;
        return;
    }

    cout << "Couldn't find Customer by Id '" << input << "'" << endl;
}

void customersView(Customer *customers, int &currentCustomerPos)
{
    cout << "-----------------------------------------------" << endl;
    cout << "Found Customers" << endl;
    cout << "-----------------------------------------------" << endl
         << endl;

    // Check if at least one Customer exist
    if (currentCustomerPos <= 0)
    {
        cout << "-> No Customer found!" << endl;
        pressEnterToContinue();
        return;
    }

    for (int i = 0; i < currentCustomerPos; i++)
    {
        Customer currentCustomer = customers[i];
        // or Customer currentCustomer = *(customers + i);

        customerView(currentCustomer);
        cout << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "-> Found " << currentCustomerPos << (currentCustomerPos > 1 ? " Customers" : " Customer") << endl;

    pressEnterToContinue();
}

void customerView(Customer customer)
{
    cout << "---------------------" << endl;
    cout << "Id: " << customer.id << endl;
    cout << "Name: '" << customer.name << "'" << endl;
    cout << "---------------------" << endl;
}

bool searchCustomerView(Customer *customers, int currentCustomerPos)
{
    int input;

    cout << "-----------------------------------------------" << endl;
    cout << "Search Customer" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "1. Search By Name" << endl;
    cout << "2. Search By Id" << endl;
    cout << "3. Go Back" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Your Input: ";
    cin >> input;

    switch (input)
    {
    case 1:
        searchCustomerByNameView(customers, currentCustomerPos);
        break;

    case 2:
        searchCustomerByIdView(customers, currentCustomerPos);
        break;

    case 3:
        clearConsole();
        return false;

    default:
        cout << endl
             << "-> Invalid Input '" << input << "'" << endl;
    }

    return true;
}

void searchCustomerByNameView(Customer *customers, int currentCustomerPos)
{
    string input;

    clearConsole();
    cout << "-----------------------------------------------" << endl;
    cout << "Search Customer by Name" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Please Enter the searched Name: ";
    cin >> input;
    clearConsole();

    FoundCustomers foundCustomers = getCustomersByName(customers, currentCustomerPos, input);

    customersView(foundCustomers.customers, foundCustomers.foundCustomerPos);
    delete[](foundCustomers.customers);
}

void searchCustomerByIdView(Customer *customers, int currentCustomerPos)
{
    string input;

    clearConsole();
    cout << "-----------------------------------------------" << endl;
    cout << "Search Customer by Id" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Please Enter the searched Id: ";
    cin >> input;
    clearConsole();

    FoundCustomers foundCustomers = getCustomersById(customers, currentCustomerPos, input);

    customersView(foundCustomers.customers, foundCustomers.foundCustomerPos);
    delete[](foundCustomers.customers);
}

void clearConsole()
{
    system("cls");
}

void pressEnterToContinue()
{
    cout << endl
         << "Press Enter to Continue\n";
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

    // Add new Customer and update currentCustomerPos
    newCustomers[newCustomerPos - 1] = newCustomer;
    currentCustomerPos = newCustomerPos;

    return newCustomers;
}

Customer *removeCustomer(Customer *customers, int &currentCustomerPos, string id)
{
    bool removedCustomer = false;
    int newCustomerPos = currentCustomerPos - 1;
    Customer *newCustomers = new Customer[newCustomerPos];

    // Filter Customer Array
    for (int i = 0; i < currentCustomerPos; i++)
    {
        if ((i == newCustomerPos && !removedCustomer) || i > newCustomerPos)
            continue;

        if (customers[i].id != id)
            newCustomers[removedCustomer ? (i - 1) : i] = customers[i];
        else
            removedCustomer = true;
    }

    // Release old used Customer Array Main Storage and update currentCustomerPos
    if (removedCustomer)
    {
        delete[](customers);
        currentCustomerPos = newCustomerPos;
        return newCustomers;
    }

    // If no Customer Removed return old Customers Pointer
    delete[](newCustomers);
    return customers;
}

FoundCustomers getCustomersByName(Customer *customers, int &currentCustomerPos, string name)
{
    int currentFoundCustomerPos = 0;
    Customer *foundCustomers = new Customer[1];

    for (int i = 0; i < currentCustomerPos; i++)
    {
        Customer currentCustomer = customers[i];
        if (currentCustomer.name.rfind(name, 0) == 0)
            foundCustomers = addCustomer(foundCustomers, currentFoundCustomerPos, currentCustomer);
    }

    // Build return Value
    FoundCustomers finalFoundCustomers;
    finalFoundCustomers.foundCustomerPos = currentFoundCustomerPos;
    finalFoundCustomers.customers = foundCustomers;

    return finalFoundCustomers;
}

FoundCustomers getCustomersById(Customer *customers, int &currentCustomerPos, string id)
{
    int currentFoundCustomerPos = 0;
    Customer *foundCustomers = new Customer[1];

    for (int i = 0; i < currentCustomerPos; i++)
    {
        Customer currentCustomer = customers[i];
        if (currentCustomer.id == id)
            foundCustomers = addCustomer(foundCustomers, currentFoundCustomerPos, currentCustomer);
    }

    // Build return Value
    FoundCustomers finalFoundCustomers;
    finalFoundCustomers.foundCustomerPos = currentFoundCustomerPos;
    finalFoundCustomers.customers = foundCustomers;

    return finalFoundCustomers;
}

int getCustomerIndexById(Customer *customers, int currentCustomerPos, string id)
{
    for (int i = 0; i < currentCustomerPos; i++)
    {
        if (customers[i].id == id)
            return i;
    }
    return -1;
}

// ==============================================================================
// Debugging
// ==============================================================================

void outputCustomers(Customer *customers, int currentCustomerPos)
{
    cout << endl;
    cout << "-Debugging-----------------" << endl;
    cout << "-> CurrentCustomerPos: " << currentCustomerPos << endl;
    for (int i = 0; i < currentCustomerPos; i++)
    {
        customerView(customers[i]);
    }
    cout << "---------------------------" << endl;
}

void fillCustomersWithDummyData(Customer *&customers, int &currentCustomerPos)
{
    Customer customer1;
    customer1.id = "1";
    customer1.name = "Hans";
    customers = addCustomer(customers, currentCustomerPos, customer1);

    Customer customer2;
    customer2.id = "2";
    customer2.name = "Dieter";
    customers = addCustomer(customers, currentCustomerPos, customer2);

    Customer customer3;
    customer3.id = "3";
    customer3.name = "Benno";
    customers = addCustomer(customers, currentCustomerPos, customer3);

    Customer customer4;
    customer4.id = "4";
    customer4.name = "Angela";
    customers = addCustomer(customers, currentCustomerPos, customer4);

    Customer customer5;
    customer5.id = "5";
    customer5.name = "Benny";
    customers = addCustomer(customers, currentCustomerPos, customer5);
}
