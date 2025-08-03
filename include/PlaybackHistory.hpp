#ifndef PLAYBACK_HISTORY_HPP
#define PLAYBACK_HISTORY_HPP

#include "Song.hpp"
#include "Playlist.hpp"
#include <stack>

class PlaybackHistory {
private:
    std::stack<Song*> history;
    Playlist& playlist; // Reference to same playlist instance

public:
    PlaybackHistory(Playlist& pl);

    void play_song(int index);       // play from playlist
    void undo_last_play();           // re-add to playlist at front
    void display_history() const;          // list history stack
};

#endif
