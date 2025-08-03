#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <iostream>
#include "Song.hpp"
#include <functional>


class Playlist{
private:
    struct Node{
        Song* song;
        Node* next;
        Node* prev;
        Node(Song* _song):song(_song),next(nullptr),prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    bool isReversed;
    int songCount;

    Node* getNodeAt(int index);

public:
    Playlist();
    ~Playlist();

    void add_song(const std::string& title, const std::string& artist, int duration);
    void delete_song(int index);
    void move_song(int from, int to);
    void reverse_playlist();
    void display();
    Song* extract_song(int index);             // new
    void add_song_to_front(Song* song);        // new
    int size() const { return songCount; }
    void for_each(const std::function<void(Song*)>& fn) const;



    
};


#endif