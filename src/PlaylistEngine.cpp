#include "Playlist.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <functional>

Playlist::Playlist() : head(nullptr), tail(nullptr), songCount(0), isReversed(false) {}

Playlist::~Playlist() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current->song;
        delete current;
        current = next;
    }
}

Playlist::Node* Playlist::getNodeAt(int index) {
    if (index < 0 || index >= songCount) throw std::out_of_range("Index out of range");

    Node* current = isReversed ? tail : head;
    if (isReversed) {
        for (int i = 0; i < index; ++i) current = current->prev;
    } else {
        for (int i = 0; i < index; ++i) current = current->next;
    }
    return current;
}


void Playlist::add_song(const std::string& title, const std::string& artist, int duration) {
    Song* newSong = new Song(generateRandomId(), title, artist, duration);
    Node* node = new Node(newSong);

    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    songCount++;
}

void Playlist::delete_song(int index) {
    Node* target = getNodeAt(index);

    if (target->prev) target->prev->next = target->next;
    else head = target->next;

    if (target->next) target->next->prev = target->prev;
    else tail = target->prev;

    delete target->song;
    delete target;
    songCount--;
}

void Playlist::move_song(int from, int to) {
    if (from == to) return;

    Node* nodeFrom = getNodeAt(from);
    Song* songToMove = nodeFrom->song;

    // Unlink nodeFrom
    if (nodeFrom->prev) nodeFrom->prev->next = nodeFrom->next;
    else head = nodeFrom->next;

    if (nodeFrom->next) nodeFrom->next->prev = nodeFrom->prev;
    else tail = nodeFrom->prev;

    delete nodeFrom;
    songCount--;

    // Insert at new position
    Node* node = new Node(songToMove);
    if (to == 0) {
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
    } else if (to >= songCount) {
        node->prev = tail;
        if (tail) tail->next = node;
        tail = node;
    } else {
        Node* nextNode = getNodeAt(to);
        node->next = nextNode;
        node->prev = nextNode->prev;
        if (nextNode->prev) nextNode->prev->next = node;
        nextNode->prev = node;
    }
    songCount++;
}

void Playlist::reverse_playlist() {
    isReversed = !isReversed;

}

void Playlist::display() {
    Node* current = isReversed ? tail : head;
    std::cout << "Playlist [" << (isReversed ? "Reversed" : "Normal") << "]:\n";
    int i = 0;
    while (current) {
        std::cout << i++ << ". " << current->song->title
                  << " by " << current->song->artist
                  << " (" << current->song->duration << " sec)\n";
        current = isReversed ? current->prev : current->next;
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
    songCount--;
    return song;
}

void Playlist::add_song_to_front(Song* song) {
    Node* node = new Node(song);
    node->next = head;
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
    songCount++;
}
void Playlist::for_each(const std::function<void(Song*)>& fn) const {
    Node* current = isReversed ? tail : head;
    while (current) {
        fn(current->song);
        current = isReversed ? current->prev : current->next;
    }
}
