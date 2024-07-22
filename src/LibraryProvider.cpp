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
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, album, artist;
        int releaseYear;
        ss >> std::quoted(title) >> std::quoted(album) >> std::quoted(artist) >> releaseYear;
        assert(ss && "Failed to read music title from file");
        musicTitles.emplace_back(title, album, artist, releaseYear);
    }
    sortMusicTitles(musicTitles);

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
    sortMusicTitles(musicTitles);
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

// Helper function to truncate string if it exceeds max length
std::string truncateString(const std::string& str, size_t maxLength) {
    if (str.length() > maxLength) {
        return str.substr(0, maxLength - 3) + "...";
    }
    return str;
}

void LibraryProvider::listMusicTitles() const {
    // musicTitles gets saved in sorted order on "LibraryProvider::loadFromFile" this way there is no need to sort again when listing all titles.
    auto sortedTitles = musicTitles;
    
    std::cout << std::left
              << std::setw(30) << "| Title"
              << std::setw(20) << "| Album"
              << std::setw(20) << "| Artist"
              << std::setw(10) << "| Year |" << std::endl;
    
    std::cout << std::setfill('-')
              << std::setw(82) << "+" << std::setfill(' ') << std::endl;
    
    for (const auto& musicTitle : sortedTitles) {
        std::cout << std::left
                  << std::setw(30) << "| " + truncateString(musicTitle.title, 28)
                  << std::setw(20) << "| " + truncateString(musicTitle.album, 18)
                  << std::setw(20) << "| " + truncateString(musicTitle.artist, 18)
                  << std::setw(10) << "| " + std::to_string(musicTitle.releaseYear) + " |" << std::endl;
    }

    std::cout << std::setfill('-')
              << std::setw(82) << "+" << std::setfill(' ') << std::endl;
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
            musicTitle.artist.find(pattern) != std::string::npos ||
            std::to_string(musicTitle.releaseYear).find(pattern) != std::string::npos) {
            std::cout << musicTitle.title << " " << musicTitle.album << " " << musicTitle.artist << " " << musicTitle.releaseYear << std::endl;
        }
    }
}