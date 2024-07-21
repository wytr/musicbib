#ifndef LIBRARYPROVIDER_H
#define LIBRARYPROVIDER_H

#include "IMusicLibrary.h"
#include "MusicTitle.h"
#include <vector>
#include <string>

class LibraryProvider : public IMusicLibrary {

public:
    std::vector<MusicTitle> musicTitles;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    void addMusicTitle(const MusicTitle& musicTitle) override;
    void listMusicTitles() const override;
    void findTitle(const std::string& title) const override;
    void search(const std::string& pattern) const override;
private:
    void sortMusicTitles(std::vector<MusicTitle>& titles) const;
};

#endif // LIBRARYPROVIDER_H
