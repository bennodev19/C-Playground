#include <iostream>
using namespace std;

// Interface
struct Employee
{
    int id;
    string name;
};

// Function declaration
void employeeInput();
void employeeOutput();

// Employes
Employee employees[100];
int nextEmployeeId = 0;

int main()
{
    char userInput;

    cout << endl
         << endl
         << endl;
    cout << "The employee list! \n";
    cout << "To leave this program enter (l)";
    cout << endl
         << endl
         << endl;

    do
    {
        cout << "Print employee (1) \n";
        cout << "Create new employee (2) \n";
        cin >> userInput;
        cout << endl
             << enld
             << endl;

        switch (userInput)
        {
        case '1':
            employeeOutput();
            break;
        case '2':
            employeeInput();
            break;
        default:
            cout << "-> Invalid input (" << userInput << ")\n\n\n";
        }
    } while (userInput != 'l');

    return 0;
}

void employeeInput()
{
    string userInput = "";

    cout << "---------------------------------------\n";

    do
    {
        Employee tempEmployee;
        tempEmployee.id = nextEmployeeId;

        // Get Name
        cout << "Please Enter an employe name \n";
        cin >> userInput;
        cout << endl;

        tempEmployee.name = userInput;

        cout << "-> Registered Employe '" << tempEmployee.name << "'\n";

        cout << "Do you want to register another employee? (y/n)\n";
        cin >> userInput;

        employees[nextEmployeeId] = tempEmployee;
        nextEmployeeId++;
    } while (userInput == "y");

    cout << "---------------------------------------\n";
    cout << endl
         << endl
         << endl;
}

void employeeOutput()
{
    cout << "---------------------------------------\n";
    cout << "Employee List: \n";

    for (int i = 0; i < nextEmployeeId; i++)
    {
        cout << "-> Id: " << employees[nextEmployeeId].id << endl;
        cout << "-> Name: " << employees[nextEmployeeId].name << endl;

        if (i != nextEmployeeId - 1)
            cout << "--\n";
    }

    cout << "---------------------------------------\n";
    cout << endl
         << endl
         << endl;
}