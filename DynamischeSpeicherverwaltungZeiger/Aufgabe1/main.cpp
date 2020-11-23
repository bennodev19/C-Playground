// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

int main()
{
    int toSaveValuesLength = 0;

    cout << "How many values would you like to save?" << endl;
    cin >> toSaveValuesLength;

    int *values = new int[toSaveValuesLength];

    cout << endl
         << endl;

    for (int i = 0; i < toSaveValuesLength; i++)
    {
        cout << "Please Enter the " << i + 1 << " value: ";
        cin >> values[i]; // or *(values + i)
    }

    cout << endl
         << endl;

    cout << "Saved values: " << endl;
    for (int i = 0; i < toSaveValuesLength; i++)
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
