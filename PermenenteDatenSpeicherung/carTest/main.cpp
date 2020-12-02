#include <iostream>
#include <string>

using namespace std;

//Deklaration der Struktur T_Fahrzeug
struct T_Fahrzeug {
	int iFahrzID;
	char acMarke[10]; // nicht den Datentyp string verwenden!!!
	float fPreis;
};

//Prototypen
void ZeigeMenue();
T_Fahrzeug EingabeFahrzeug(int iAnzahl);
void AusgabeFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahl);
bool ExportFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahl, string FileName);
void InitialisierenFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahlMax);
int AnzahlFahrzeugeErkunden(T_Fahrzeug * meineFahrzeuge, int iAnzahlMax);

int main() {
	int iMaxAnzahl = 100;
	int iAktuelleAnzahl = 0;
	char cEingabe = ' ';
	int iEingabe = 0;

	locale::global(locale("German"));

	const string FileName = "SicherungAlleFahrzeuge.nettmann";

	T_Fahrzeug * meineFahrzeuge = new T_Fahrzeug[iMaxAnzahl];
	InitialisierenFahrzeuge(meineFahrzeuge, iMaxAnzahl);

	do {
		ZeigeMenue();
		cin >> iEingabe;
		switch (iEingabe) {
		case 1: //Ausgabe der Fahrzeuge
			if (iAktuelleAnzahl == 0) {
				cout << "keine Fahrzeuge vorhanden!" << endl;
			}
			else {
				AusgabeFahrzeuge(meineFahrzeuge, iAktuelleAnzahl);
			}
			break;
		case 2: //Fahrzeuge importieren (Datei lesen)
				// Noch nicht umgesetzt.
			cout << "Funktion noch nicht vorhanden! ";
			break;
		case 3: //Fahrzeug hinzufügen
			while (iAktuelleAnzahl < iMaxAnzahl)
			{
				do {
					cEingabe = ' ';
					meineFahrzeuge[iAktuelleAnzahl] = EingabeFahrzeug(iAktuelleAnzahl);
					iAktuelleAnzahl++;
					cout << "Möchten Sie ein Fahrzeug hinzufügen? (j/...): ";
					cin >> cEingabe;

				} while (cEingabe == 'j');
				break;
			}
			break;
		case 4: //fahrzeug loeschen (Falls nicht möglich, dann erscheint Fehlermeldung)
				// Noch nicht umgesetzt.
			cout << "Funktion noch nicht vorhanden! ";
			break;
		case 5: //alle maximal möglichen Fahrzeuge exportieren (Datei schreiben)
			if (ExportFahrzeuge(meineFahrzeuge, iMaxAnzahl, FileName) == false) {
				cout << "Warnung: Fahrzeugexport fehlgeschlagen. " << endl;
			};
			break;
		case 6: //
			cout << "Auf Wiedersehen " << endl;
			break;
		default:
			cout << "Eingabe ungültig! \a";
			break;
		}
		system("pause");
	} while (iEingabe != 6);

	return 0;
}

//Gibt das Menü aus.
void ZeigeMenue() {
	system("CLS");
	cout << "   _   _      _   _                                " << endl;
	cout << "  | \\ | |    | | | |                              " << endl;
	cout << "  |  \\| | ___| |_| |_ _ __ ___   __ _ _ __  _ __  " << endl;
	cout << "  | . ` |/ _ \\ __| __| '_ ` _ \\ / _` | '_ \\| '_ \\ " << endl;
	cout << "  \\_| \\_/\\___|\\__|\\__|_| |_| |_|\\__,_|_| |_|_| |_|" << endl;
	cout << "                                                  " << endl;

	cout << "<1> Fahrzeuge anzeigen" << endl;
	cout << "<2> Fahrzeuge importieren" << endl;
	cout << "<3> Fahrzeug hinzufügen" << endl;
	cout << "<4> Fahrzeug löschen" << endl;
	cout << "<5> Fahrzeuge exportieren" << endl;
	cout << "<6> Programm beenden: " << endl;
	cout << "Auswahl: ";
}

//Fahrzeugnummer aller Fahrzeuge wird mit 0 initialisiert, um gültige Datensätze von ungültigen zu unterscheiden
void InitialisierenFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahlMax)
{
	for (int i = 0; i < iAnzahlMax; i++) {
		meineFahrzeuge[i].iFahrzID = 0;
		}
}

//Zählt die Anzahl der aktuell vorhandenen gültigen Datensätze (z. B. nach dem Einlesen aller maximal möglichen Datensätze aus der Datei)
int AnzahlFahrzeugeErkunden(T_Fahrzeug * meineFahrzeuge, int iAnzahlMax)
{
	int iAktuelleAnzahl = 0;
	for (int i = 0; i < iAnzahlMax; i++) {
		if(meineFahrzeuge[i].iFahrzID != 0)
			iAktuelleAnzahl++;
	}

	return iAktuelleAnzahl;
}

//Ermöglicht die Eingabe eines neuen Fahrzeugs
T_Fahrzeug EingabeFahrzeug(int iAnzahl) {

	T_Fahrzeug Auto;
	string strEingabe;

	Auto.iFahrzID = iAnzahl + 1;
	cout << "\tFahrzeug-Nr: " << Auto.iFahrzID << endl;
	cout << "\tMarke: ";
	cin >> Auto.acMarke;
	cout << "\tPreis: ";
	cin >> Auto.fPreis;
	cout << endl;
	return Auto;
}

//Gibt die Fahrzeuge aus
void AusgabeFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahl) {

	cout << endl << "ID \tMarke \tPreis" << endl;
	for (int i = 0; i < iAnzahl; i++) {

		cout << meineFahrzeuge[i].iFahrzID << "\t";
		cout << meineFahrzeuge[i].acMarke << "\t";
		cout << meineFahrzeuge[i].fPreis << " EUR " << endl;
	}
	cout << endl;
}

//Exportiert die Fahrzeuge in eine Datei
bool ExportFahrzeuge(T_Fahrzeug * meineFahrzeuge, int iAnzahl, string FileName) {

	FILE * fpDatei;

	fopen(&fpDatei, FileName.c_str(), "w"); // TODO 
	// TODO Prüfen, ob Datei wirklich geöffnet werden konnte
	fwrite(&iAnzahl, sizeof(int), 1, fpDatei); 
	
	fwrite(meineFahrzeuge, sizeof(T_Fahrzeug), iAnzahl, fpDatei);


	// TODO DAtei wird nicht geschrieben, da Inhalt nur in Puffer
	// z.B. durch schließen der Datei

	return true;
}