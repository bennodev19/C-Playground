// https://lernplattform.mebis.bayern.de/pluginfile.php/33521533/mod_resource/content/1/040_DynamischeSpeicherverwaltungZeiger_V4_Sch%C3%BCler.pdf

#include <iostream>

using namespace std;

void addNewValue(int *value, int maxValueCount, int& currentValuePos);
int getMaxValues();
bool calculate(int *value, int currentValuePos);
bool menu(int *values, int maxValueCount, int& currentValuePos);

int main() {
   int maxValueCount = getMaxValues();
   int currentValuePos = 0;

   int *values = new int[maxValueCount];

   while(menu(values, maxValueCount, currentValuePos));

   delete[](values);
   values = nullptr;
}

bool menu(int *values, int maxValueCount, int& currentValuePos){
   int input;

   cout << "-----------------------------" << endl;
   cout << "1. Add Value" << endl;
   cout << "2. Calculate" << endl;
   cout << "3. End" << endl;
    cout << "-----------------------------" << endl << endl;
   cin >> input;

   switch (input)
   {
   case 1:
       addNewValue(values, maxValueCount, currentValuePos);
       break;

    case 2:
       return !calculate(values, currentValuePos);
       break;

    case 3:
       return false;
       break;
   
   default:
       cout << endl << "Invalid Input '" << input << "'" << endl;
       break;
   }
    
    return true;
}

int getMaxValues(){
    int input = 0;
    cout << "How many values would you like to enter" << endl;
    cin >> input;
    return input;
}

bool calculate(int *values, int currentValuePos){
    if(currentValuePos <= 0){
        cout << "Please enter some values first!";
        return false;
    }

   for(int i = 0; i < currentValuePos; i++){
       cout << values[i] << endl;
   }
   return true;
}

void addNewValue(int *values, int maxValueCount, int& currentValuePos){
    if(currentValuePos >= maxValueCount){
       cout << "To many Values entered" << endl;
       return;
    }

    cout << "Add new Value" << endl;
    cin >> values[currentValuePos]; 
    // or *(value + currentValuePos)
    currentValuePos++;
}