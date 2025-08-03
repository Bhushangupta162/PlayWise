#ifndef SONG_INDEX_HPP
#define SONG_INDEX_HPP

#include "Song.hpp"
#include <string>
#include <unordered_map>

class SongIndex {
private:
    std::unordered_map<std::string, Song*> idMap;
    std::unordered_map<std::string, Song*> titleMap;

public:
    void add_song(Song* song);
    void remove_song(const std::string& song_id);
    
    Song* find_by_id(const std::string& song_id) const;
    Song* find_by_title(const std::string& title) const;

    void display_index(); // Debug view
};

#endif
