// https://lernplattform.mebis.bayern.de/pluginfile.php/36133652/mod_resource/content/0/20%20INFO-Dateiverarbeitung_V08.pdf

#include <iostream>
using namespace std;

int main() {
    // 1. Dateizeiger definieren
    FILE* fpDatei = nullptr;

    // 2. Datei öffnen
    // fopen_s(Zeiger auf Dateizeiger, Dateiname, Zugriffsmodus);
    fopen_s(&fpDatei, "myFirstFile.jeff", "w"); 

    // Zugriffsmodus                                       Zugriffsmodus
    // Bewirkt:                                           |  r  |  w  |  a  |
    //                                                    -------------------
    // Datei ist lesbar                                   |  x  |     |     |
    // Datei ist beschribbar                              |     |  x  |  x  |
    // Vorhandener Dateiinhalt wird gelöscht              |     |  x  |     |
    // Vorhandener Dateinhalt bleibt erhalten             |     |     |  x  |
    // und neue Inhalte ans Ende der Datei geschrieben 

    // r = read
    // Lesen der Datei

    // w = write
    // Erstellt Datei wenn nicht vorhanden und überschreibe alte Daten fals vorhanden

    // a = appent
    // Erstellt Datei wenn nicht vorhanden und hänge Daten an alte Daten hinten an false vorhanden

    // 3. Prüfung ob Datei erfolgreich geöffnet/angelegt wurde    (z.B. Fehler wenn keine Rechte auf Ordner zuzugreifen bei 'w' access)
    if(fpDatei == nullptr){
        cout << "Fehler: Datei konnte nicht gefunden werden.";
        return 0;
    } 

    // 4. Datei bearbeiten


    // 5. Datei schließen !!
    fclose(fpDatei);

    return 0;   
}