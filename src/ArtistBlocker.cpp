#include "ArtistBlocker.hpp"
#include <iostream>

void ArtistBlocker::block_artist(const std::string& artist) {
    blocklist.insert(artist);
}

void ArtistBlocker::unblock_artist(const std::string& artist) {
    blocklist.erase(artist);
}

bool ArtistBlocker::is_blocked(const std::string& artist) const {
    return blocklist.find(artist) != blocklist.end();
}

void ArtistBlocker::display_blocklist() const {
    std::cout << " Blocked Artists:\n";
    for (const auto& name : blocklist) {
        std::cout << "- " << name << "\n";
    }
}
