#ifndef ARTIST_BLOCKER_HPP
#define ARTIST_BLOCKER_HPP

#include <string>
#include <unordered_set>

class ArtistBlocker {
private:
    std::unordered_set<std::string> blocklist;

public:
    void block_artist(const std::string& artist);
    void unblock_artist(const std::string& artist);
    bool is_blocked(const std::string& artist) const;

    void display_blocklist() const;
};

#endif
