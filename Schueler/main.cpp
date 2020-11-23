#include <iostream>
using namespace std;

// Interface
struct Student
{
    int id;
    string firstName;
    string lastName;
    int grades[3]
};

// Function declaration
void createStudent();
void printStudents();
void addGradeToStudent();

// Students
const int studentCount = 10;
Student students[studentCount];
int nextStudentId = 0;

int main()
{
    char userInput;

    cout << endl
         << endl
         << endl;
    cout << "The students list! \n";
    cout << "To leave this program enter (l)";
    cout << endl
         << endl
         << endl;

    do
    {
        cout << "Print students (1) \n";
        cout << "Create new Students (2) \n";
        cout << "Give Student a grade (3)\n";
        cin >> userInput;
        cout << endl
             << endl
             << endl;

        switch (userInput)
        {
        case '1':
            printStudents();
            break;

        case '2':
            createStudent();
            break;

        case '3':
            addGradeToStudent();
            break;

        case 'l':
            return 0;

        default:
            cout << "-> Invalid input (" << userInput << ")\n\n\n";
        }
    } while (userInput != 'l');

    return 0;
}

//