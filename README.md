# Studentenverwaltung_C_DHBW
Studentenverwaltung in C

## Anforderungen

### Finale Aufgabe testolos
Das Programm soll eine Liste von Studenten verarbeiten. Das Programm soll darauf ausgelegt, benutzerfreundlich und intuitiv bedienbar zu sein. Es bietet eine klare und übersichtliche Benutzeroberfläche, die es dem Benutzer ermöglicht, schnell und einfach durch die verschiedenen Funktionen zu navigieren.
- Benutzerfreundlichkeit:
Das Programm wurde so gestaltet, dass es auch für weniger erfahrene Benutzer leicht verständlich ist. Alle Eingabefelder sind klar beschriftet, und die Benutzerführung ist logisch strukturiert.
- Fehlerbehandlung:
Bei fehlerhaften Eingaben wird der Benutzer sofort durch klare Fehlermeldungen oder Hinweise informiert. Diese Rückmeldungen helfen dem Benutzer, Eingabefehler schnell zu erkennen und zu korrigieren, wodurch die Benutzererfahrung verbessert wird.
- Intuitive Bedienbarkeit:
Die Funktionen sind so angeordnet, dass der Benutzer ohne umfangreiche Einarbeitung alle notwendigen Aktionen durchführen kann. Menüs und Optionen sind selbsterklärend, was die Interaktion mit dem Programm erleichtert.
### Anforderungen:
1. Studentenstruktur:
  1.1 Erstelle eine Studentenstruktur mit folgenden Inhalten:
    - Vorname
    - Nachname
    - Studiengang
    - Matrikelnummer
    - Startdatum
    - Enddatum
    - Geburtsdatum
2. Datumsstruktur:
  2.1 Erstelle eine Datumsstruktur (Tag, Monat, Jahr) für das Geburtsdatum und Einschreibungsdaten etc.
3. Funktion inputStudent:
  3.1 Schreibe eine Funktion, bei der der Benutzer alle relevanten Daten zu einem Studenten eingeben kann.
4. Funktion addStudent:
  4.1 Schreibe eine Funktion, bei der ein Student in der Struktur hinzugefügt wird.
5. Funktion countStudents:
  5.1 Schreibe eine Funktion, die die Anzahl der gespeicherten Studenten zurückgibt.
6. Funktion printStudent(Matrikelnummer):
  6.1 Schreibe eine Funktion, mit der ein Student auf dem Bildschirm ausgegeben werden kann.
7. Funktion printAllStudents:
  7.1 Schreibe eine Funktion, mit der alle Studenten alphabetisch auf dem Bildschirm ausgegeben werden.
8. Funktion deleteStudent(Matrikelnummer):
  8.1 Schreibe eine Funktion, die einen Studenten löscht.
9. Funktion save:
  9.1 Schreibe eine Funktion, die alle gespeicherten Studenten in eine Textdatei (z.B. im CSV-Format) speichert. Diese Funktion soll beim Beenden des Programms automatisch aufgerufen werden und somit nicht im Menü auftauchen.
  9.2 Der Benutzer soll von der Speicherung der Daten im Hintergrund nichts mitbekommen. Es dürfen keine Fehlermeldungen angezeigt werden, wenn die Datei nicht existiert oder nicht gespeichert werden kann.
10. Funktion read:
  10.1 Schreibe eine Funktion, die eine Datei ausliest und alle Studenten daraus ins Programm lädt. Diese Funktion soll beim Start des Programms automatisch aufgerufen werden und somit nicht im Menü auftauchen.
  10.2 Auch hier soll der Benutzer von der Ladeoperation im Hintergrund nichts mitbekommen. Es dürfen keine Fehlermeldungen angezeigt werden, wenn die Datei nicht gefunden wird oder nicht geladen werden kann.
11. Verkettete Listen:
  11.1 Die Aufgabe soll mithilfe von verketteten Listen gelöst werden.
12. Datenvalidierung: Bei der Eingabe der Daten für einen Studenten müssen folgende Validierungen durchgeführt werden:
  12.1 Namen: Der Vor- und Nachname darf nur alphabetische Zeichen enthalten und muss zwischen 1 und 50 Zeichen lang sein. Bei ungültiger Eingabe wird der Benutzer ebenfalls zur Korrektur aufgefordert.
  12.2Geburtsdatum: Das Geburtsdatum muss im Format TT.MM.JJJJ eingegeben werden. Es wird überprüft, ob das Datum gültig ist (z.B. kein 30. Februar) und dass der Student mindestens 18 Jahre alt ist.
  12.3 Startdatum: Das Startdatum muss im gleichen Format wie das Geburtsdatum eingegeben werden und muss nach dem Geburtsdatum liegen. Bei ungültiger Eingabe wird der Benutzer zur Korrektur aufgefordert.
  12.4 Enddatum: Das Enddatum muss ebenfalls im Format TT.MM.JJJJ eingegeben werden und muss nach dem Startdatum liegen.
13. Einzigartigkeit der Matrikelnummer: Es muss sichergestellt werden, dass die Matrikelnummer einzigartig ist.
  13.1 Matrikelnummer: Die Matrikelnummer muss eine positive Ganzzahl sein und aus genau 8 Ziffern bestehen.

### Abgabeanforderungen

Bei der Abgabe des Projekts sind folgende Anforderungen zu beachten:

- Dokumentation: Es soll ein PDF abgegeben werden, das detaillierte Erklärungen zu jeder implementierten Funktion enthält. Jede Erklärung sollte eine kurze Zusammenfassung der Funktionalität der jeweiligen Funktion geben, gefolgt von einer detaillierten Beschreibung, wie sie implementiert wurde.
- Source Files: Es müssen alle relevanten Source Files in den Formaten .c und .h abgegeben werden. Diese Dateien enthalten den Quellcode des Programms.
- Keine Projektdateien: Es dürfen keine Projektdateien oder Executables (ausführbare Dateien) eingereicht werden. Die Abgabe sollte sich ausschließlich auf die Quellcodedateien beschränken.

### Video-Demonstration
- Inhalt des Videos: Das Video soll eine umfassende Demonstration des Programms bieten (kein Quellcode). Es sollten alle Funktionalitäten des Programms gezeigt werden.
- Fehlerbehandlung: Es sollen auch Szenarien demonstriert werden, in denen fehlerhafte Eingaben gemacht werden, sowie die entsprechenden Fehlermeldungen oder Hinweise, die das Programm bereitstellt und wie das Programm darauf reagiert.
- Neuladen des Programms: Die Demonstration soll die Funktionalität des Neuladens des Programms umfassen, wobei gezeigt wird, wie alle zuvor eingetragenen Daten geladen werden.
- Anzeige der Textdatei: Während der Präsentation soll die Textdatei, in der die Daten gespeichert sind, sichtbar gemacht werden, um die Struktur und den Inhalt der gespeicherten Daten zu verdeutlichen.
