#include "SongIndex.hpp"
#include <iostream>

void SongIndex::add_song(Song* song) {
    if (song) {
        idMap[song->id] = song;
        titleMap[song->title] = song;
    }
}

void SongIndex::remove_song(const std::string& song_id) {
    Song* song = find_by_id(song_id);
    if (!song) return;

    titleMap.erase(song->title);
    idMap.erase(song_id);
}

Song* SongIndex::find_by_id(const std::string& song_id) const {
    auto it = idMap.find(song_id);
    return it != idMap.end() ? it->second : nullptr;
}

Song* SongIndex::find_by_title(const std::string& title) const {
    auto it = titleMap.find(title);
    return it != titleMap.end() ? it->second : nullptr;
}

void SongIndex::display_index() {
    std::cout << " Current Song Index:\n";
    for (auto it = idMap.begin(); it != idMap.end(); ++it) {
        std::string id = it->first;
        Song* song = it->second;
        std::cout << "- ID: " << id << ", Title: " << song->title
                  << ", Artist: " << song->artist << "\n";
    }
}

