#include "LibraryProvider.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>

void LibraryProvider::loadFromFile(const std::string& filename) {
    assert(!filename.empty() && "Filename should not be empty");

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    // TODO: Sort Items before placing into std::vector<MusicTitle> (Output of list-command will be sorted)
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, album, artist;
        int releaseYear;
        ss >> std::quoted(title) >> std::quoted(album) >> std::quoted(artist) >> releaseYear;
        assert(ss && "Failed to read music title from file");
        musicTitles.emplace_back(title, album, artist, releaseYear);
    }

    file.close();
}

void LibraryProvider::saveToFile(const std::string& filename) const {
    // TODO: Save the sorted library
    assert(!filename.empty() && "Filename should not be empty");

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    for (const auto& musicTitle : musicTitles) {
        file << std::quoted(musicTitle.title) << " " << std::quoted(musicTitle.album) << " "
             << std::quoted(musicTitle.artist) << " " << musicTitle.releaseYear << "\n";
    }

    file.close();
}

void LibraryProvider::addMusicTitle(const MusicTitle& musicTitle) {
    assert(!musicTitle.title.empty() && "Title should not be empty");
    assert(!musicTitle.album.empty() && "Album should not be empty");
    assert(!musicTitle.artist.empty() && "Artist should not be empty");
    assert(musicTitle.releaseYear > 0 && "Release year should be positive");

    musicTitles.push_back(musicTitle);
}

void LibraryProvider::listMusicTitles() const {
    auto sortedTitles = musicTitles;
    std::sort(sortedTitles.begin(), sortedTitles.end(), [](const MusicTitle& a, const MusicTitle& b) {
        if (a.artist == b.artist) {
            if (a.album == b.album) {
                return a.title < b.title;
            }
            return a.album < b.album;
        }
        return a.artist < b.artist;
    });

    for (const auto& musicTitle : sortedTitles) {
        std::cout << musicTitle.title << " " << musicTitle.album << " " << musicTitle.artist << " " << musicTitle.releaseYear << std::endl;
    }
}

void LibraryProvider::findTitle(const std::string& title) const {
    assert(!title.empty() && "Title should not be empty");

    for (const auto& musicTitle : musicTitles) {
        if (musicTitle.title == title) {
            std::cout << musicTitle.title << " " << musicTitle.album << " " << musicTitle.artist << " " << musicTitle.releaseYear << std::endl;
        }
    }
}

void LibraryProvider::search(const std::string& pattern) const {
    // TODO: different search patterns/options
    assert(!pattern.empty() && "Search pattern should not be empty");

    for (const auto& musicTitle : musicTitles) {
        if (musicTitle.title.find(pattern) != std::string::npos ||
            musicTitle.album.find(pattern) != std::string::npos ||
            musicTitle.artist.find(pattern) != std::string::npos) {
            std::cout << musicTitle.title << " " << musicTitle.album << " " << musicTitle.artist << " " << musicTitle.releaseYear << std::endl;
        }
    }
}
