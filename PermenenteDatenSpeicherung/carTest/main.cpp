#include <iostream>
#include <string>

using namespace std;

struct Car {
	int id;
	char brand[20]; 
	float price;
};

// UI
bool menuView(Car *&cars, int &currentCarPos, int maxCarCount);
void addCarView(Car*& cars, int& currentCarPos, int maxCarCount);
void carsView(Car* cars, int currentCarPos);
void carView(Car car);
void clearConsole();
void pressEnterToContinue();

// Logic
Car* addCar(Car* cars, int& currentCarPos, Car newCar);
bool exportCars(Car* cars, int currentCarPos, string fileName);
bool importCars(Car*& cars, int& currentCarPos, string fileName);

// Debugging
void fillCarsWithDummyData(Car*& cars, int& currentCarPos);

const string fileName = "SicherungAlleFahrzeuge.nettmann";

int main() {
	int maxCarCount = 100;
	int currentCarPos = 0;
	Car* cars = new Car[1];

	locale::global(locale("German"));

	// fillCarsWithDummyData(cars, currentCarPos);

	// Import Cars
	if (!importCars(cars, currentCarPos, fileName))
		cerr << "-> Failed to import Cars" << endl;
	else
		cout << "-> Successfully imported " << currentCarPos << " Cars" << endl;

	while (menuView(cars, currentCarPos, maxCarCount));

	// Export Cars
	if (!exportCars(cars, currentCarPos, fileName))
		cerr << "-> Failed to export Cars" << endl;
	else
		cout << "-> Successfully exported " << currentCarPos << " Cars" << endl;


	pressEnterToContinue();

	// Clear used space in main memory
	delete[](cars);
	cars = nullptr;

	return 0;
}

bool menuView(Car*& cars, int& currentCarPos, int maxCarCount) {
	int input;

	cout << "-----------------------------------------------" << endl;
	cout << "   _   _      _   _                                " << endl;
	cout << "  | \\ | |    | | | |                              " << endl;
	cout << "  |  \\| | ___| |_| |_ _ __ ___   __ _ _ __  _ __  " << endl;
	cout << "  | . ` |/ _ \\ __| __| '_ ` _ \\ / _` | '_ \\| '_ \\ " << endl;
	cout << "  \\_| \\_/\\___|\\__|\\__|_| |_| |_|\\__,_|_| |_|_| |_|" << endl;
	cout << "                                                  " << endl;

	cout << "<1> Display Cars" << endl;
	cout << "<2> Add Car" << endl;
	cout << "<3> Delete Car" << endl;
	cout << "<4> End" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Your Input: ";
	cin >> input;

	clearConsole();

	switch (input) {

	case 1:
		carsView(cars, currentCarPos);
		break;

	case 2:
		addCarView(cars, currentCarPos, maxCarCount);
		break;

	case 3:
		// TODO
		break;

	case 4:
		return false;

	default:
		cerr << endl
			<< "-> Invalid Input '" << input << "'" << endl;
	}

	return true;
}

void addCarView(Car*& cars, int& currentCarPos, int maxCarCount) {
	string input;
	float price;
	char brand[10];

	cout << "-----------------------------------------------" << endl;
	cout << "Add Car" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Car Brand: ";
	cin >> brand;
	cout << "Car Price: ";
	cin >> price;
	cout << "-----------------------------------------------" << endl;

	// Create new Car
	Car newCar;
	newCar.id = currentCarPos + 1;
	strcpy_s(newCar.brand, brand);
	newCar.price = price;

	clearConsole();
	carView(newCar);
	cout << "Is that correct? (y/n)" << endl;
	cin >> input;

	// Add Car
	if (input == "y")
	{
		cars = addCar(cars, currentCarPos, newCar);
		clearConsole();
		cout << "-> Sucessfully added Customer" << endl;
		return;
	}

	clearConsole();
	cout << "-> Sucessfully cancled creation of Customer" << endl;
}

void carsView(Car* cars, int currentCarPos) {
	cout << "-----------------------------------------------" << endl;
	cout << "Found Cars" << endl;
	cout << "-----------------------------------------------" << endl
		<< endl;

	// Check if at least one Car exist
	if (currentCarPos <= 0)
	{
		cout << "-> No Car found!" << endl;
		pressEnterToContinue();
		return;
	}

	for (int i = 0; i < currentCarPos; i++)
	{
		carView(cars[i]);
		cout << endl;
	}
	cout << "-----------------------------------------------" << endl;
	cout << "-> Found " << currentCarPos << (currentCarPos > 1 ? " Cars" : " Car") << endl;

	pressEnterToContinue();
}

void carView(Car car)
{
	cout << "---------------------" << endl;
	cout << "Id: " << car.id << endl;
	cout << "Brand: '" << car.brand << "'" << endl;
	cout << "Price: '" << car.price << "'" << endl;
	cout << "---------------------" << endl;
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

bool exportCars(Car* cars, int currentCarPos, string fileName) {
	FILE* file = nullptr;
	int carCount = currentCarPos; // Because we are having no leaks in our array currentCarPos === currentCarCount

	// Open File
	fopen_s(&file, fileName.c_str(), "w");

	// Check if File got sucessfully opened
	if (file == nullptr) {
		cerr << "-> Couldn't find file by name '" << fileName << "'" << endl;
		return false;
	}

	/* OLD way | saving array based on array size
	// Write carCount into File
    fwrite(&currentCarPos, sizeof(int), 1, file);
	
	// Write currentCarPos cars into File
	fwrite(cars, sizeof(Car), currentCarPos, file);
	*/

	// Write cars into File
	fwrite(cars, sizeof(Car), currentCarPos, file);
	
	// Close File
	fclose(file);

	return true;
}

bool importCars(Car*& cars, int& currentCarPos, string fileName) {
	FILE* file = nullptr;

	// Open File
	fopen_s(&file, fileName.c_str(), "r");

	// Check if File got sucessfully opened
	if (file == nullptr) {
		cerr << "-> Couldn't find file by name '" << fileName << "'" << endl;
		return false;
	}

	/* OLD way | reading array based on array size
	// Read carCount from File
    fread(&currentCarPos, sizeof(int), 1, file);

	// Read currentCarPos cars from File
	fread(cars, sizeof(Car), currentCarPos, file);
	*/

	Car temp;

	// Read cars from File as long the FilePointer hasn't reached the end
	do {
		// Read 1 car from File and save it in temp variable to check if its valid
		fread(&temp, sizeof(Car), 1, file);

		// If FileReader Pointer isn't at the end of the file (eof = end of file)
		if (!feof(file))
			cars = addCar(cars, currentCarPos, temp);
	} while (!feof(file));

	// Close File
	fclose(file);

	return true;
}

Car* addCar(Car* cars, int& currentCarPos, Car newCar)
{
	int newCustomerPos = currentCarPos + 1;
	Car* newCars = new Car[newCustomerPos];

	// Copy old Car Array into new Customer Array
	for (int i = 0; i < currentCarPos; i++)
	{
		newCars[i] = cars[i];
		// or *(newCars + i) = *(cars + i);
	}

	// Release old used Car Array Main Storage
	delete[](cars);

	// Add new Customer and update currentCustomerPos
	newCars[newCustomerPos - 1] = newCar;
	currentCarPos = newCustomerPos;

	return newCars;
}

// ==============================================================================
// Debugging
// ==============================================================================

void fillCarsWithDummyData(Car*& cars, int& currentCarPos)
{
	Car car1;
	car1.id = 1;
    strcpy_s(car1.brand, "Audi");
	car1.price = 1000.8f;
	cars = addCar(cars, currentCarPos, car1);

	Car car2;
	car2.id = 2;
	strcpy_s(car2.brand, "BMW");
	car2.price = 2800.0f;
	cars = addCar(cars, currentCarPos, car2);
}