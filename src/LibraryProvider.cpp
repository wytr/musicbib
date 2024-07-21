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

    std::vector<MusicTitle> tempTitles;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, album, artist;
        int releaseYear;
        ss >> std::quoted(title) >> std::quoted(album) >> std::quoted(artist) >> releaseYear;
        assert(ss && "Failed to read music title from file");
        tempTitles.emplace_back(title, album, artist, releaseYear);
    }

    sortMusicTitles(tempTitles);
    musicTitles = std::move(tempTitles);

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

    // Find the correct position to insert the new title to maintain sorted order
    auto it = std::lower_bound(musicTitles.begin(), musicTitles.end(), musicTitle, [](const MusicTitle& a, const MusicTitle& b) {
        if (a.artist == b.artist) {
            if (a.album == b.album) {
                return a.title < b.title;
            }
            return a.album < b.album;
        }
        return a.artist < b.artist;
    });

    musicTitles.insert(it, musicTitle);
}

void LibraryProvider::listMusicTitles() const {
    // musicTitles gets saved in sorted order on "LibraryProvider::loadFromFile" this way there is no need to sort again when listing all titles.
    auto sortedTitles = musicTitles;
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
    assert(!pattern.empty() && "Search pattern should not be empty");

    for (const auto& musicTitle : musicTitles) {
        if (musicTitle.title.find(pattern) != std::string::npos ||
            musicTitle.album.find(pattern) != std::string::npos ||
            musicTitle.artist.find(pattern) != std::string::npos) {
            std::cout << musicTitle.title << " " << musicTitle.album << " " << musicTitle.artist << " " << musicTitle.releaseYear << std::endl;
        }
    }
}

void LibraryProvider::sortMusicTitles(std::vector<MusicTitle>& titles) const {
    std::sort(titles.begin(), titles.end(), [](const MusicTitle& a, const MusicTitle& b) {
        if (a.artist == b.artist) {
            if (a.album == b.album) {
                return a.title < b.title;
            }
            return a.album < b.album;
        }
        return a.artist < b.artist;
    });
}