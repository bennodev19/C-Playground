#include <iostream>

using namespace std;

int *valueToAsciiValue(char *pointerChar);

int main()
{
    char input[21];
    int *asciiArrayStartPointer; // Points at the first position of the asciiValues in function

    cout << "Please enter a String \n";
    cin >> input;

    /* Test if char array really ends at '/0
    for(int i = 0; input[i] != '\0'; i++){
        cout << input[i];
    }
    cout << endl;
    */

    asciiArrayStartPointer = valueToAsciiValue(input);

    // TODO remove
    cout << "IGNORE THIS below!!\n";
    cout << asciiArrayStartPointer << endl;
    cout << *asciiArrayStartPointer << endl;
    
    // cout << valueToAsciiValue(input) << endl;
    // cout << *valueToAsciiValue(input) << endl;

    /*
    for (int i = 0; *asciiArrayPointer > 0; i++)
    {
        cout << input[i] << "            " << asciiArrayPointer[i] << endl;
    }
    */

    cout << endl
         << endl;

    return 0;
}

int *valueToAsciiValue(char *pointerChar)
{
    int asciiValues[20];
    // or int* asciiValueFirstItemPointer = &asciiValues[0];

    for (int i = 0; i < pointerChar[i] != '\0'; i++)
    {      
        cout << pointerChar[i] << " / " << (int)pointerChar[i] << " / " << *(pointerChar + i) << &pointerChar[i] << endl;
        // or asciiValueFirstItemPointer[i] = (int)pointerChar[i];
        asciiValues[i] = (int)pointerChar[i];
    }
 
    return asciiValues; // Returns a pointer, which points at the first item of the array
}