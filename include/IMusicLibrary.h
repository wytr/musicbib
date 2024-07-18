#ifndef IMUSICLIBRARY_H
#define IMUSICLIBRARY_H

#include "MusicTitle.h"
#include <vector>
#include <string>

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

#endif // IMUSICLIBRARY_H
