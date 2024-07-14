#include "MusicTitle.h"
#include <cassert>

MusicTitle::MusicTitle(const std::string& title, const std::string& album, const std::string& artist, int releaseYear)
    : title(title), album(album), artist(artist), releaseYear(releaseYear) {
    assert(!title.empty() && "Title should not be empty");
    assert(!album.empty() && "Album should not be empty");
    assert(!artist.empty() && "Artist should not be empty");
    assert(releaseYear > 0 && "Release year should be positive");
}
