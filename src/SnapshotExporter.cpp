#include "SnapshotExporter.hpp"
#include "Sorter.hpp"
#include <iostream>
#include <map>
#include <stack>
#include <functional>

// --- Helper ---
static std::vector<Song*> playlist_to_vector(const Playlist& pl) {
    std::vector<Song*> result;
    pl.for_each([&](Song* s) {
        result.push_back(s);
    });
    return result;
}

// -- Export Function --
void SnapshotExporter::export_snapshot(const Playlist& playlist,
                                       const PlaybackHistory& history,
                                       const RatingTree& ratingTree) {
    std::cout << "\n📊 System Snapshot Dashboard\n";

    // 1. Top 5 Longest Songs
    std::vector<Song*> allSongs = playlist_to_vector(playlist);
    Sorter::merge_sort(allSongs, Sorter::compare_by_duration_desc);

    std::cout << "\n🏆 Top 5 Longest Songs:\n";
    for (int i = 0; i < std::min(5, (int)allSongs.size()); ++i) {
        Song* s = allSongs[i];
        std::cout << i + 1 << ". " << s->title << " - " << s->duration << "s\n";
    }

    // 2. Recently Played Songs
    std::cout << "\n🕘 Recently Played Songs:\n";
    history.display_history();

    // 3. Song Count by Rating
    std::cout << "\n⭐ Song Count by Rating:\n";
    for (int r = 1; r <= 5; ++r) {
        auto songs = ratingTree.search_by_rating(r);
        std::cout << "Rating " << r << ": " << songs.size() << " song(s)\n";
    }
}
