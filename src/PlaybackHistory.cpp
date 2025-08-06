#include "PlaybackHistory.hpp"
#include <iostream>
#include <stdexcept>

PlaybackHistory::PlaybackHistory(Playlist& pl) : playlist(pl) {}

void PlaybackHistory::play_song(int index) {
    Song* song = playlist.extract_song(index);
    if (!song) throw std::runtime_error("Invalid song index");
    history.push(song);
    std::cout << " Playing: " << song->title << " by " << song->artist << "\n";
}

void PlaybackHistory::undo_last_play() {
    if (history.empty()) {
        std::cout << "No recent song to undo.\n";
        return;
    }
    Song* song = history.top(); history.pop();
    playlist.add_song_to_front(song);
    std::cout << " Undo: " << song->title << " re-added to playlist.\n";
}

void PlaybackHistory::display_history() const {
    std::stack<Song*> temp = history;
    std::cout << "Recently Played:\n";
    while (!temp.empty()) {
        Song* s = temp.top(); temp.pop();
        std::cout << "- " << s->title << " by " << s->artist << "\n";
    }
}
//