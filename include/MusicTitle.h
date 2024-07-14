#ifndef MUSICTITLE_H
#define MUSICTITLE_H

#include <string>

class MusicTitle {
public:
    std::string title;
    std::string album;
    std::string artist;
    int releaseYear;

    MusicTitle(const std::string& title, const std::string& album, const std::string& artist, int releaseYear);
};

#endif // MUSICTITLE_H
