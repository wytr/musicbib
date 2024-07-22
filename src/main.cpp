#include "LibraryProvider.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

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
    IMusicLibrary* libraryProvider = new LibraryProvider();
    libraryProvider->loadFromFile(filename);

    std::string command = argv[1];

    if (command == "list") {
        libraryProvider->listMusicTitles();
    } else if (command == "find" && argc == 3) {
        libraryProvider->findTitle(argv[2]);
    } else if (command == "search" && argc == 3) {
        libraryProvider->search(argv[2]);
    } else if (command == "add" && argc == 6) {
        std::string title = argv[2];
        std::string album = argv[3];
        std::string artist = argv[4];
        try {
            int year = std::stoi(argv[5]);
            if (year <= 0) {
                throw std::invalid_argument("Year should be a positive integer");
            }
            libraryProvider->addMusicTitle(MusicTitle(title, album, artist, year));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid year format. Year should be a positive integer.\n";
            printUsage();
            delete libraryProvider;
            return 1;
        }catch (const std::out_of_range& e) {
            std::cerr << "hello man of the future. your year unfortunately reaches int overflow.\n";
            printUsage();
            delete libraryProvider;
            return 1;
        }
    } else {
        printUsage();
        delete libraryProvider;
        return 1;
    }

    libraryProvider->saveToFile(filename);
    delete libraryProvider;
    return 0;
}
