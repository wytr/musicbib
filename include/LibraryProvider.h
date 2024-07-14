#ifndef LIBRARYPROVIDER_H
#define LIBRARYPROVIDER_H

#include "MusicTitle.h"
#include <vector>
#include <string>

class LibraryProvider {
public:
    std::vector<MusicTitle> musicTitles;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void addMusicTitle(const MusicTitle& musicTitle);
    void listMusicTitles() const;
    void findTitle(const std::string& title) const;
    void search(const std::string& pattern) const;
};

#endif // LIBRARYPROVIDER_H
