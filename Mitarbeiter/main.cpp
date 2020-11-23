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
const int employeeCount = 1;
Employee employees[employeeCount];
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
             << endl
             << endl;

        switch (userInput)
        {
        case '1':
            employeeOutput();
            break;

        case '2':
            employeeInput();
            break;

        case 'l':
            return 0;

        default:
            cout << "-> Invalid input (" << userInput << ")\n\n\n";
        }
    } while (userInput != 'l');

    return 0;
}

void employeeInput()
{
    string userInput;

    cout << "Create Employee\n";
    cout << "---------------------------------------\n";

    do
    {
        Employee tempEmployee;

        // Check if max employee count has been reached
        if (nextEmployeeId >= employeeCount)
        {
            cout << "\n\nMax employee count reached!\n\n";
            break;
        }

        // Assign Id to Employee
        tempEmployee.id = nextEmployeeId;

        // Get Name
        cout << "Please Enter the name of the new employee \n";
        cin >> userInput;
        cout << endl;

        // Set Employee Name
        tempEmployee.name = userInput;

        cout << "-> Registered employee '" << tempEmployee.name << "'\n";

        cout << "Do you want to register another employee? (y/n)\n";
        cin >> userInput;

        // Add Employee to Array
        employees[nextEmployeeId] = tempEmployee;

        // Increment Id (Index)
        nextEmployeeId++;
    } while (userInput == "y");

    cout << "---------------------------------------\n";
    cout << endl
         << endl
         << endl;
}

void employeeOutput()
{
    cout << "Employee List: \n";
    cout << "---------------------------------------\n";

    // Print Employees
    for (int i = 0; i < nextEmployeeId; i++)
    {
        cout << "-> Id: " << employees[i].id << endl;
        cout << "-> Name: " << employees[i].name << endl;

        // Print seperator
        if (i != nextEmployeeId - 1)
            cout << "--\n";
    }

    // If nextEmployeeId is 0 (initial Value) the company has no employees
    if (nextEmployeeId == 0)
        cout << "\nNo Employee found!\n\n";

    cout << "---------------------------------------\n";
    cout << endl
         << endl
         << endl;
}