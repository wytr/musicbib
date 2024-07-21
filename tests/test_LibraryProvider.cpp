#include <gtest/gtest.h>
#include "LibraryProvider.h"
#include <sstream>
#include <iostream>

class LibraryProviderTest : public ::testing::Test {
protected:
    void SetUp() override {
        libraryProvider.addMusicTitle(MusicTitle("TestTitle1", "TestAlbum1", "TestArtist1", 2001));
        libraryProvider.addMusicTitle(MusicTitle("TestTitle2", "TestAlbum2", "TestArtist2", 2002));
    }

    LibraryProvider libraryProvider;
};

TEST_F(LibraryProviderTest, AddMusicTitle) {
    std::ostringstream output;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(output.rdbuf());
    
    libraryProvider.addMusicTitle(MusicTitle("NewTitle", "NewAlbum", "NewArtist", 2020));
    libraryProvider.listMusicTitles();
    
    std::cout.rdbuf(oldCoutStreamBuf);
    
    ASSERT_NE(output.str().find("NewTitle"), std::string::npos);
}

TEST_F(LibraryProviderTest, FindTitle) {
    std::ostringstream output;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(output.rdbuf());
    
    libraryProvider.findTitle("TestTitle1");
    
    std::cout.rdbuf(oldCoutStreamBuf);
    
    ASSERT_NE(output.str().find("TestTitle1"), std::string::npos);
}

TEST_F(LibraryProviderTest, SearchPattern) {
    std::ostringstream output;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(output.rdbuf());
    
    libraryProvider.search("Test");
    
    std::cout.rdbuf(oldCoutStreamBuf);
    
    ASSERT_NE(output.str().find("TestTitle1"), std::string::npos);
    ASSERT_NE(output.str().find("TestTitle2"), std::string::npos);
}
