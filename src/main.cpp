#include "LibraryProvider.h"
#include <iostream>
#include <string>
#include <cassert>

void printUsage() {
    std::cout << "Usage: musicbib <command> [<parameter>]\n"
              << "Commands:\n"
              << "  list\n"
              << "  find <title>\n"
              << "  search <pattern>\n"
              << "  add <title> <album> <artist> <year>\n";
}

int main(int argc, char* argv[]) {
    assert(argc > 0 && "Argument count should be greater than 0");

    if (argc < 2) {
        printUsage();
        return 1;
    }

    const std::string filename = "musiclibrary.txt";
    LibraryProvider libraryProvider;
    libraryProvider.loadFromFile(filename);

    std::string command = argv[1];

    if (command == "list") {
        libraryProvider.listMusicTitles();
    } else if (command == "find" && argc == 3) {
        libraryProvider.findTitle(argv[2]);
    } else if (command == "search" && argc == 3) {
        libraryProvider.search(argv[2]);
    } else if (command == "add" && argc == 6) {
        std::string title = argv[2];
        std::string album = argv[3];
        std::string artist = argv[4];
        int year = std::stoi(argv[5]);
        assert(year > 0 && "Year should be a positive integer");
        libraryProvider.addMusicTitle(MusicTitle(title, album, artist, year));
    } else {
        printUsage();
        return 1;
    }

    libraryProvider.saveToFile(filename);
    return 0;
}
