// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

int main()
{
    int maxToSaveValuesLength = 0;
    int enteredValuesLength = 0;
    char input;

    cout << "How many values would you like to save (max)?" << endl;
    cin >> maxToSaveValuesLength;

    int *values = new int(maxToSaveValuesLength); // Speicher wird zur Laufzeit 'freigegeben'
    // void dummyFunction(int &enteredValuesLength) -> & erstellt reference -> wenn in funcion enteredValuesLength geänderwird ändert sich auch hier das enteredValuesLength

    cout << endl
         << endl;

    do
    {
        cout << "Would you like to enter a new value? (y/n)";
        cin >> input;

        switch (input)
        {
        case 'y':
            cout << "Please enter the " << enteredValuesLength + 1 << " Value: ";
            cin >> values[enteredValuesLength];
            enteredValuesLength++;
            break;
        case 'n':
            break;
        default:
            cout << "-> Invalid input '" << input << "'";
        }
    } while (input != 'n' && enteredValuesLength < maxToSaveValuesLength);

    cout << endl
         << endl;

    // Message if maxValues reached
    if (enteredValuesLength >= maxToSaveValuesLength)
    {
        cout << "-> Max values reached!\n";
        cout << endl
             << endl;
    }

    cout << "Saved values: " << endl;
    for (int i = 0; i < enteredValuesLength; i++)
    {
        cout << i + 1 << " Value: " << values[i] << endl;           // short form of form below
        cout << i + 1 << ".1 Value: " << *(values + i) << endl;     // 'values' is here source adress of first element in the array -> we add i to the source adress -> so in this case always i * 4 because of 4 byes of the int and than we get the value at the source adress with *
        cout << i + 1 << ".2 Value: " << *(&values[0] + i) << endl; // we get the source adress with & at the first element of the array -> ..
        cout << i + 1 << " Adress: " << &values[i] << endl
             << endl;
    }

    // Release storage again (Always if using the 'new' operator)
    delete[](values);
    values = nullptr;

    return 0;
}
