# Musikbibliothek CLI Programm

## Überblick

Dies ist ein Kommandozeilen-Interface (CLI) Programm zur Verwaltung einer Musikbibliothek. Das Programm ermöglicht es Ihnen, Musiktitel aus einer Datei zu laden, zu speichern, aufzulisten, zu finden und nach Mustern zu suchen. Es unterstützt auch das Hinzufügen neuer Musiktitel.

## Funktionen

- Musiktitel aus einer Datei laden.
- Musiktitel in einer Datei speichern.
- Alle Musiktitel sortiert nach Künstler, Album und Titel auflisten.
- Einen Musiktitel nach seinem Namen suchen.
- Nach Mustern in Titeln, Alben oder Künstlernamen suchen.
- Neue Musiktitel zur Bibliothek hinzufügen.

## Installation

### Voraussetzungen

- g++ Compiler
- CMake (optional, wenn Sie die bereitgestellte `CMakeLists.txt` verwenden)
- VS Code (optional, für die Entwicklung)

### Einrichtung

1. Klonen Sie das Repository.
    ```sh
    git clone https://github.com/wytr/musicbib.git
    cd musicbib
    ```

## Nutzung

### Befehle

- **Alle Musiktitel auflisten:**
  ```sh
  ./musicbib list
- **Einen bestimmten Titel finden:**
  ```sh
  ./musicbib find <title>
- **Nach einem Muster in Titeln, Alben oder Künstlern suchen:**
  ```sh
  ./musicbib search <pattern>
- **Einen neuen Musiktitel hinzufügen:**
  ```sh
  ./musicbib add <title> <album> <artist> <year>

### Format der Bibliothek (musiclibrary.txt)
Die Datei sollte Einträge im folgenden Format enthalten:
  ```sh
  "title" "album" "artist" year
  ```
### Designentscheidungen und Reflektion

#### Designentscheidungen

1. **Einsatz konkreter Klassen:**
   - **`MusicTitle` Klasse:** Diese Klasse repräsentiert einen Musiktitel mit den Attributen Titel, Album, Künstler und Erscheinungsjahr. Eine konkrete Klasse wurde hier gewählt, da sie eine spezifische und eindeutige Datenstruktur benötigt, um Musiktitel zu repräsentieren. Die Rolle dieser Klasse ist es, als Datencontainer zu fungieren und die grundlegenden Informationen eines Musiktitels zu speichern.
   - **`LibraryProvider` Klasse:** Diese Klasse verwaltet eine Sammlung von `MusicTitle` Objekten. Sie bietet Funktionen zum Laden und Speichern der Bibliothek aus/in eine Datei, zum Hinzufügen neuer Titel, zum Auflisten aller Titel sowie zum Suchen und Finden von Titeln. <del>Diese Klasse wurde als konkrete Klasse gestaltet, um eine zentrale Stelle für alle Operationen zu bieten, die auf die Musiksammlung angewendet werden.</del>
   - **`IMusicLibrary` Interface:** Um die einfache Implementierung weiterer Provider zu erlauben wurde im Anschluss auf einem Feature-Branch die Abstraktion eingeführt. Damit könnte nun beispielsweise ein Provider implementiert werden, der das Dateiformat JSON unterstützt. Hierzu würde ich die Library von [nlohmann](https://github.com/nlohmann/json) verwenden.
2. **Keine Einführung von Interfaces oder abstrakten Klassen: (veraltet/wenn eine einfache Textdatei reicht! KEEP IT SIMPLE STUPID)** 
   - **Warum keine Interfaces oder abstrakten Klassen?** Da das Programm relativ klein und spezifisch ist, war die Einführung von Interfaces oder abstrakten Klassen nicht notwendig. Die Verwendung von konkreten Klassen bietet ausreichend Flexibilität und Einfachheit für die gegebenen Anforderungen. Die Struktur des Programms ist direkt und ohne unnötige Abstraktionen gehalten, was die Verständlichkeit und Wartbarkeit verbessert.

#### Alternativen und Überlegungen

- **Verwendung von abstrakten Klassen oder Interfaces:**
  - **Alternative:** Eine mögliche Alternative wäre die Einführung eines Interfaces wie `IMusicLibrary`, das grundlegende Operationen wie `loadFromFile`, `saveToFile`, `addMusicTitle`, `listMusicTitles`, `findTitle` und `search` definiert. `LibraryProvider` könnte dann dieses Interface implementieren.
  - **Gründe gegen die Alternative:** Für die aktuelle Größe und Komplexität des Projekts würde die Einführung eines Interfaces zusätzlichen Overhead und Komplexität ohne einen signifikanten Nutzen hinzufügen. Interfaces sind besonders nützlich, wenn mehrere Implementierungen desselben Interfaces erforderlich sind, was hier nicht der Fall ist.
  - **Siehe Branch "IMusicLibrary"**

```
class IMusicLibrary {
public:
    virtual ~IMusicLibrary() = default;

    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual void addMusicTitle(const MusicTitle& musicTitle) = 0;
    virtual void listMusicTitles() const = 0;
    virtual void findTitle(const std::string& title) const = 0;
    virtual void search(const std::string& pattern) const = 0;
};
```
#### Reflektion über die Arbeit

- **Besondere Highlights:**
  - **Klare und einfache Struktur:** Das Programm hat eine klare und einfache Struktur, was die Verständlichkeit und Wartbarkeit verbessert.
  - **Einsatz von Assertions:** Die Verwendung von Assertions hilft, Fehler frühzeitig zu erkennen und sicherzustellen, dass die Eingabedaten den erwarteten Bedingungen entsprechen.

- **Besondere Schwachstellen:**
  - **Fehlende Abstraktion für zukünftige Erweiterungen:** Sollte das Programm in Zukunft erweitert werden (z.B. durch Unterstützung für mehrere Dateiformate oder erweiterte Suchfunktionen), könnte das Fehlen von Interfaces oder abstrakten Klassen die Erweiterbarkeit einschränken. Diese Schwachstelle wurde nicht beseitigt, da die aktuelle Implementierung die Anforderungen vollständig erfüllt und die Einfachheit der Struktur beibehalten wurde.
  - **Fehlende Fehlerbehandlung:** Derzeit gibt es eine begrenzte Fehlerbehandlung, insbesondere bei Dateioperationen. Verbesserte Fehlerbehandlung könnte implementiert werden, um das Programm robuster zu machen. Dies wurde nicht weiter verfolgt, um die Einfachheit des Codes zu bewahren und den Fokus auf die grundlegenden Funktionen zu legen.

#### Fazit

Die Designentscheidungen basieren auf der aktuellen Größe und Komplexität des Projekts sowie den spezifischen Anforderungen. Durch die Verwendung konkreter Klassen und die Vermeidung unnötiger Abstraktionen bleibt der Code einfach und wartbar. Zukünftige Erweiterungen könnten von einer Überarbeitung der Struktur profitieren, um Interfaces oder abstrakte Klassen einzuführen, falls komplexere Anforderungen entstehen.
