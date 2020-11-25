// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

// Logic
int *addNewValue(int *values, int &currentValuePos, int valueToAdd);
float calculate(int *values, int currentValuePos);

// UI
bool menu(int *&values, int &currentValuePos);
void addNewValueView(int *&values, int &currentValuePos);
void calculateValueView(int *values, int currentValuePos);
void clearConsole();

// Debuggin
void outputValues(int *values, int currentValuePos);

int main()
{
    int currentValuePos = 0;
    int *values = new int[1]; // Reserve dummy storage

    while(menu(values, currentValuePos));

    // Clear used space in main memory
    delete[](values);
    values = nullptr;
}

bool menu(int *&values, int &currentValuePos)
{
    int input;

    cout << "--------------------------------" << endl;
    cout << "1. Add Value" << endl;
    cout << "2. Calculate Mean Value" << endl;
    cout << "3. End" << endl;
    cout << "-------------------------------" << endl;
    cin >> input;

    clearConsole();

    switch (input)
    {
    case 1:
        addNewValueView(values, currentValuePos);
        break;

    case 2:
        calculateValueView(values, currentValuePos);
        break;

    case 3:
        return false;
        break;

    default:
        cout << endl
             << "-> Invalid Input '" << input << "'" << endl;
    }

    return true;
}

void addNewValueView(int *&values, int &currentValuePos)
{
    int input;

    cout << "Please ener your wished Value:" << endl;
    cin >> input;

    clearConsole();
    cout << "-> You added the Value '" << input << "'" << endl;

    values = addNewValue(values, currentValuePos, input);
}

void calculateValueView(int *values, int currentValuePos)
{
    if (currentValuePos <= 0)
    {
        cout << "-> Please enter some values first!";
    }

    cout << "-> Your Mean Value is: " << calculate(values, currentValuePos) << endl;
}

int *addNewValue(int *values, int &currentValuePos, int valueToAdd)
{
    int newCurrentValuePos = currentValuePos + 1;
    int *newValues = new int[newCurrentValuePos];

    for (int i = 0; i < currentValuePos; i++)
    {
        newValues[i] = values[i];
        // or *(newValues + i) = *(values + i)
    }

    // Remove old Values form Main Storage
    delete[](values);

    newValues[newCurrentValuePos - 1] = valueToAdd;
    currentValuePos = newCurrentValuePos;

       outputValues(values, currentValuePos);
       outputValues(newValues, currentValuePos);

    return newValues;
}

float calculate(int *values, int currentValuePos)
{
    int sum = 0;

    if (currentValuePos <= 0)
        return -1;

    for (int i = 0; i < currentValuePos; i++)
    {
        sum += values[i];
        // or sum += *(values + i)
    }

    return sum / 2;
}

void clearConsole()
{
    system("CLEAR");
}

void outputValues(int* values, int currentValuePos){
    cout << endl;
    cout << "-Debugging-----------------" << endl;
    for (int i = 0; i < currentValuePos; i++)
    {
        cout << values[i] << endl;
    } 
    cout << "-> CurrentValuePos: " << currentValuePos << endl;
    cout << "---------------------------" << endl;
}
