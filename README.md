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
