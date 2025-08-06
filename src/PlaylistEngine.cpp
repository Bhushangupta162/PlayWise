#include "Playlist.hpp"
#include "utils.hpp"
#include <iostream>
#include <stdexcept>

Playlist::Playlist() : head(nullptr), tail(nullptr), songCount(0), isReversed(false) {}

Playlist::~Playlist() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr->song;
        delete curr;
        curr = next;
    }
}

Playlist::Node* Playlist::getNodeAt(int index) {
    if (index < 0 || index >= songCount) throw std::out_of_range("Invalid index");
    Node* curr = isReversed ? tail : head;
    for (int i = 0; i < index; ++i) {
        curr = isReversed ? curr->prev : curr->next;
    }
    return curr;
}

void Playlist::add_song(const std::string& title, const std::string& artist, int duration) {
    Song* song = new Song(generateRandomId(), title, artist, duration);
    Node* node = new Node(song);

    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++songCount;
}

void Playlist::delete_song(int index) {
    Node* node = getNodeAt(index);

    if (node->prev) node->prev->next = node->next;
    else head = node->next;

    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;

    delete node->song;
    delete node;
    --songCount;
}

void Playlist::move_song(int from, int to) {
    if (from == to) return;

    Node* node = getNodeAt(from);
    Song* song = node->song;

    if (node->prev) node->prev->next = node->next;
    else head = node->next;
    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;
    delete node;
    --songCount;

    Node* newNode = new Node(song);
    if (to <= 0) {
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
    } else if (to >= songCount) {
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
    } else {
        Node* curr = getNodeAt(to);
        newNode->next = curr;
        newNode->prev = curr->prev;
        if (curr->prev) curr->prev->next = newNode;
        curr->prev = newNode;
    }
    ++songCount;
}

void Playlist::reverse_playlist() {
    isReversed = !isReversed;
}

void Playlist::display() {
    Node* curr = isReversed ? tail : head;
    std::cout << "Playlist [" << (isReversed ? "Reversed" : "Normal") << "]:\n";
    int idx = 0;
    while (curr) {
        std::cout << idx++ << ". " << curr->song->title << " by " << curr->song->artist
                  << " (" << curr->song->duration << " sec)\n";
        curr = isReversed ? curr->prev : curr->next;
    }
    std::cout << std::endl;
}

Song* Playlist::extract_song(int index) {
    Node* node = getNodeAt(index);
    Song* song = node->song;

    if (node->prev) node->prev->next = node->next;
    else head = node->next;
    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;

    delete node;
    --songCount;
    return song;
}

void Playlist::add_song_to_front(Song* song) {
    Node* node = new Node(song);
    node->next = head;
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
    ++songCount;
}

void Playlist::for_each(const std::function<void(Song*)>& fn) const {
    Node* current = isReversed ? tail : head;
    while (current) {
        fn(current->song);
        current = isReversed ? current->prev : current->next;
    }
}
//