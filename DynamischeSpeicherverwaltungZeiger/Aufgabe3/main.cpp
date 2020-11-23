// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

int main()
{
    int enteredValuesLength = 0;
    int *values = new int[1]; // Reserve dummy storage
    char input;

    cout << "Enter values:" << endl
         << endl;

    do
    {
        cout << "Would you like to enter a new value? (y/n)";
        cin >> input;

        switch (input)
        {
        case 'y':
        { // { because of https://stackoverflow.com/questions/34829955/what-is-causing-this-cannot-jump-from-switch-statement-to-this-case-label
          // Inspired by:
          // https://stackoverflow.com/questions/13431567/how-to-make-an-array-with-a-dynamic-size-general-usage-of-dynamic-arrays-maybe
           
            // Create new myGrownValues Pointer which reserved one more storage as values
            int *myGrownValues = new int[enteredValuesLength + 1];

            // Copy values into myGrownValues
            for (int i = 0; i < enteredValuesLength; i++)
            {
                myGrownValues[i] = values[i];
            }

            // Set Input into myGrownValues at last position
            cout << "Please enter the " << enteredValuesLength + 1 << " Value: ";
            cin >> myGrownValues[enteredValuesLength];

            // Release reserved storage of values and remove pointer of it
            delete[](values);
            values = nullptr;

            // Set values first element pointer to myGrownValues first element pointer
            values = myGrownValues;

            enteredValuesLength++;
            break;
        }

        case 'n':
            break;

        default:
            cout << "-> Invalid input '" << input << "'";
        }
    } while (input != 'n');

    cout << endl
         << endl;

    cout << "Saved values: " << endl;
    for (int i = 0; i < enteredValuesLength; i++)
    {
        cout << i + 1 << " Value: " << values[i] << endl;           // short form of form below
        cout << i + 1 << ".1 Value: " << *(values + i) << endl;     // 'values' is here source adress of first element in the array -> we add i to the source adress -> so in this case always i * 4 because of 4 byes of the int and than we get the value at the source adress with *
        cout << i + 1 << ".2 Value: " << *(&values[0] + i) << endl; // we get the source adress with & at the first element of the array -> ..
        cout << i + 1 << " Address: " << &values[i] << endl
             << endl;
    }

    // Release storage again (Always if using the 'new' operator)
    delete[](values);
    values = nullptr;

    return 0;
}
