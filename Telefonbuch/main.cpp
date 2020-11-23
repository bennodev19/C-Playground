#include <iostream>
#include <list>
using namespace std;

// Interface
struct Contact
{
    int id;
    string name;
    string number;
};

struct Item
{
    bool isSet;
    Contact contact;
};

struct Settings
{
    bool sortedByName;
};

// Render
void renderContacts();
void renderCreateContact();
void renderSearchContact();
void renderDeleteContact();
void renderSettings();
void renderPressEnterToContinue();
void clearConsole();

// Logic
int getFreeIndex();                 // Returns free Index.. if no free Index found it return -1
int getContactIndexById(string id); // Return index of contact by id if no Index found it return -1
Contact getContactById(string id);
bool contactByIdExsts(string id);
bool deleteContactById(string id);
bool createContact(string name, string number);
Contact *findContactsByName(string name);
void sortContactsByName();
void sortContactsById();

// Dummy
void createTestData();

// Contacts
const int contactSize = 10;
Item contactList[contactSize];

int nextContactId = 0;

// Settings
Settings settings;

int main()
{
    char userInput;

    // Fill contactStatuses
    for (int i = 0; i < contactSize; i++)
    {
        contactList[i].isSet = false;
    };

    // Instantiate Settings
    settings.sortedByName = false;

    // Fill in dummy data
    createTestData();

    do
    {
        cout << "---------------------------------------------------------\n";
        cout << " Mein Telefonbuch:\n";
        cout << "---------------------------------------------------------\n";
        cout << " 1. Telefonbuch anzeigen\n";
        cout << " 2. Neuen Eintrag anlegen\n";
        cout << " 3. Suche Einträge anhand des Names\n";
        cout << " 4. Lösche Einträge anhand der Identifikations-Nummer\n";
        cout << " 5. Settings\n";
        cout << " 6. Beenden\n";
        cout << "---------------------------------------------------------\n";
        cout << endl;
        cout << "Ihre Auswahl: ";
        cin >> userInput;
        cout << endl
             << endl
             << endl;

        switch (userInput)
        {
        case '1':
            renderContacts();
            break;

        case '2':
            renderCreateContact();
            break;

        case '3':
            renderSearchContact();
            break;

        case '4':
            renderDeleteContact();
            break;

        case '5':
            renderSettings();
            break;

        case '6':
            return 0;

        default:
            cout << "-> Invalid input (" << userInput << ")\n\n\n";
        }
    } while (userInput != '6');

    return 0;
}

void renderContacts()
{
    bool printedContact = false;
    int foundContactsCount = 0;

    // Sort Contacts (TODO not clean)
    if (settings.sortedByName)
        sortContactsByName();
    else
        sortContactsById();

    clearConsole();
    cout << "---------------------------------------------------------\n";
    cout << " Deine Kontakte: \n";
    cout << "---------------------------------------------------------\n\n";
    for (int i = 0; i < contactSize; i++)
    {
        // Check if contact is set
        if (contactList[i].isSet)
        {
            cout << (foundContactsCount + 1) << ". Kontakt: \n";
            cout << "Id: " << contactList[i].contact.id << endl;
            cout << "Name: " << contactList[i].contact.name << endl;
            cout << "Telefonnummer: " << contactList[i].contact.number << endl;
            cout << endl;

            foundContactsCount++;
            printedContact = true;
        }
    }
    cout << "---------------------------------------------------------\n\n";

    // Print No Contact
    if (!printedContact)
        cout << "-> Du hast keine Kontakte!\n\n";
    else
        cout << "-> " << foundContactsCount << " Kontakte gefunden\n\n";

    renderPressEnterToContinue();
}

void renderCreateContact()
{
    string name = "";
    string phoneNumber = "";

    clearConsole();
    cout << "Neuen Kontakt erstellen: \n";
    cout << "Name: ";
    cin >> name;
    cout << "Telefonnummer: ";
    cin >> phoneNumber;
    cout << endl
         << endl;

    // Create Contact
    bool success = createContact(name, phoneNumber);

    // Check if PhoneBook is full
    if (!success)
    {
        cout << "-> Dein Telefonbuch is voll!\n\n";
        renderPressEnterToContinue();
        return;
    }
    cout << "-> Erfolgreich Kontakt angelegt\n\n";
    renderPressEnterToContinue();
}

void renderSearchContact()
{
    string searchName;
    bool printedContact = false;
    int foundContactsCount = 0;

    clearConsole();
    cout << "Kontakte suchen: \n";
    cout << "Name: ";
    cin >> searchName;
    cout << endl
         << endl;

    // Doesn't work yet
    // Contact* foundContacts = findContactsByName(searchName);

    clearConsole();
    cout << "---------------------------------------------------------\n";
    cout << " Gefundene Kontakte: \n";
    cout << "---------------------------------------------------------\n\n";
    for (int i = 0; i < contactSize; i++)
    {
        // Check if contact names matches with searchName
        if (contactList[i].contact.name.rfind(searchName, 0) == 0)
        {
            cout << (foundContactsCount + 1) << ". Kontakt: \n";
            cout << "Id: " << contactList[i].contact.id << endl;
            cout << "Name: " << contactList[i].contact.name << endl;
            cout << "Telefonnummer: " << contactList[i].contact.number << endl;
            cout << endl;

            foundContactsCount++;
            printedContact = true;
        }
    }
    cout << "---------------------------------------------------------\n\n";

    // Print No Contact
    if (!printedContact)
        cout << "-> Keinen Kontakt mit dem Namen '" << searchName << "' gefunden!\n\n";
    else
        cout << "-> " << foundContactsCount << " Kontakte gefunden\n\n";

    renderPressEnterToContinue();
}

void renderDeleteContact()
{
    string id;

    clearConsole();
    cout << "Kontakt löschen: \n";
    cout << "Id: ";
    cin >> id;
    cout << endl
         << endl;

    // Get Contact Index
    bool success = deleteContactById(id);

    // Check if contact exists
    if (!success)
    {
        cout << "-> Kontakt an mit der id '" << id << "' existiert nicht!\n\n";
        renderPressEnterToContinue();
        return;
    }

    cout << "-> Erfolgreich Kontakt mit der id '" << id << "' gelöscht\n\n";
    renderPressEnterToContinue();
}

void renderSettings()
{
    char userInput;

    do
    {
        clearConsole();
        cout << "---------------------------------------------------------\n";
        cout << " Settings: \n";
        cout << "---------------------------------------------------------\n";
        cout << " 1. Telefonbuch nach Name Sortieren           " << (settings.sortedByName ? "(x)" : "( )") << endl;
        cout << " 2. Zurück\n";
        cout << "---------------------------------------------------------\n";
        cout << endl;
        cout << "Ihre Auswahl: ";
        cin >> userInput;
        cout << endl
             << endl
             << endl;

        switch (userInput)
        {
        case '1':
            settings.sortedByName = !settings.sortedByName;
            break;

        case '2':
            clearConsole();
            return;

        default:
            cout << "-> Invalid input (" << userInput << ")\n\n\n";
            break;
        }
    } while (userInput != '2');
}

void renderPressEnterToContinue()
{
    cout << "Press Enter to Continue\n";
    cin.ignore(10, '\n');
    cin.get();
    clearConsole();
}

void clearConsole()
{
    system("CLEAR");
}

int getFreeIndex()
{
    for (int i = 0; i < contactSize; i++)
    {
        if (!contactList[i].isSet)
            return i;
    }
    return -1;
}

int getContactIndexById(string id)
{
    for (int i = 0; i < contactSize; i++)
    {
        if (to_string(contactList[i].contact.id) == id)
            return i;
    }
    return -1;
}

Contact getContactById(string id)
{
    int index = getContactIndexById(id);
    if (index == -1)
        return {0};
    return contactList[index].contact;
}

bool contactByIdExists(string id)
{
    return getContactIndexById(id) != -1;
}

bool deleteContactById(string id)
{
    // Get Contact Index
    int index = getContactIndexById(id);
    if (index == -1)
        return false;

    // Remove Contact from ContactList
    contactList[index].contact = (Contact){0};
    contactList[index].isSet = false;

    return true;
}

bool createContact(string name, string number)
{
    Contact contact;

    // Create Contact
    contact.id = nextContactId;
    contact.name = name;
    contact.number = number;

    // Increase nextContactId (-> unique id)
    nextContactId++;

    // Find free Index
    int index = getFreeIndex();

    // If no free index found return false
    if (index == -1)
        return false;

    // Add Contact to ContactList
    contactList[index].contact = contact;
    contactList[index].isSet = true;

    return true;
}

// TODO doesn't work yet
Contact *findContactsByName(string name)
{
    Contact *contacts;

    for (int i = 0; i < contactSize; i++)
    {
        Contact contact = contactList[i].contact;
        string foundName = contact.name;

        if (foundName.rfind(name, 0) == 0)
        {
            // Matching value
            cout << contact.name;
        }
    }
    return contacts;
}

void sortContactsByName()
{
    for (int i = 0; i < contactSize - 1; i++)
    {
        for (int j = 0; j < contactSize - i - 1; j++)
        {
            if (!contactList[i].isSet)
                continue;

            if (contactList[j].contact.name > contactList[j + 1].contact.name)
            {
                if (!contactList[j].isSet)
                    continue;

                // swap temp
                Item temp = contactList[j];
                contactList[j] = contactList[j + 1];
                contactList[j + 1] = temp;
            }
        }
    }
}

void sortContactsById()
{
    for (int i = 0; i < contactSize - 1; i++)
    {
        for (int j = 0; j < contactSize - i - 1; j++)
        {
            if (!contactList[i].isSet)
                continue;

            if (contactList[j].contact.id > contactList[j + 1].contact.id)
            {
                if (!contactList[j].isSet)
                    continue;

                // swap temp
                Item temp = contactList[j];
                contactList[j] = contactList[j + 1];
                contactList[j + 1] = temp;
            }
        }
    }
}

// Dummy

void createTestData()
{
    createContact("Franz", "0000000000001");
    createContact("Hans", "0000000000002");
    createContact("Dieter", "0000000000003");
    createContact("Paul", "0000000000004");
    createContact("Klaudia", "0000000000005");
    createContact("Franziska", "0000000000006");
    createContact("Benno", "0000000000007");
    createContact("Bennie", "0000000000008");
}