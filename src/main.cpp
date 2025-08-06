#include <iostream>
#include "Song.hpp"
#include "utils.hpp"
#include "Playlist.hpp"
#include "PlaybackHistory.hpp"
#include "RatingTree.hpp"
#include "SongIndex.hpp"
#include "Sorter.hpp"
#include "SnapshotExporter.hpp"
#include "ArtistBlocker.hpp"
#include "DurationAnalyzer.hpp"

int main() {
    std::cout << "=== PlayWise Demo ===\n\n";

    // Playlist operations
    Playlist playlist;
    playlist.add_song("Imagine", "John Lennon", 183);
    playlist.add_song("Bohemian Rhapsody", "Queen", 354);
    playlist.add_song("Hey Jude", "The Beatles", 431);

    std::cout << "Initial Playlist:\n";
    playlist.display();

    playlist.move_song(2, 0);
    std::cout << "After moving song:\n";
    playlist.display();

    playlist.reverse_playlist();
    std::cout << "Reversed playlist:\n";
    playlist.display();

    if (playlist.size() > 1) {
        playlist.delete_song(1);
        std::cout << "After deletion:\n";
        playlist.display();
    }

    // Playback history
    PlaybackHistory history(playlist);
    if (playlist.size() > 1) history.play_song(1);
    if (playlist.size() > 0) history.play_song(0);

    std::cout << "Playback history:\n";
    history.display_history();

    history.undo_last_play();
    std::cout << "After undo:\n";
    playlist.display();

    // Ratings
    RatingTree ratingTree;
    ratingTree.insert_song(new Song(generateRandomId(), "Let It Be", "The Beatles", 243), 5);
    ratingTree.insert_song(new Song(generateRandomId(), "In the End", "Linkin Park", 4), 4);
    ratingTree.insert_song(new Song(generateRandomId(), "Lose Yourself", "Eminem", 5), 5);
    ratingTree.insert_song(new Song(generateRandomId(), "Fix You", "Coldplay", 3), 3);

    std::cout << "Ratings:\n";
    ratingTree.display();

    auto topRated = ratingTree.search_by_rating(5);
    std::cout << "Songs with rating 5:\n";
    for (auto s : topRated)
        std::cout << s->title << " - " << s->artist << "\n";

    if (!topRated.empty()) ratingTree.delete_song(topRated[0]->id);
    std::cout << "After deletion in rating tree:\n";
    ratingTree.display();

    // Song indexing
    SongIndex index;
    Song* s1 = new Song(generateRandomId(), "Blinding Lights", "The Weeknd", 201);
    Song* s2 = new Song(generateRandomId(), "Rolling in the Deep", "Adele", 228);
    index.add_song(s1);
    index.add_song(s2);

    std::cout << "Song Index:\n";
    index.display_index();

    Song* found = index.find_by_id(s1->id);
    if (found)
        std::cout << "Found by ID: " << found->title << "\n";

    index.remove_song(s1->id);
    std::cout << "Post-removal check: "
              << (index.find_by_id(s1->id) ? "Exists" : "Removed") << "\n";

    // Sorting
    std::vector<Song*> songs = {
        new Song(generateRandomId(), "Viva La Vida", "Coldplay", 242),
        new Song(generateRandomId(), "Yesterday", "The Beatles", 145),
        new Song(generateRandomId(), "One Dance", "Drake", 173)
    };

    std::cout << "Original songs:\n";
    for (auto s : songs) std::cout << s->title << " (" << s->duration << "s)\n";

    Sorter::merge_sort(songs, Sorter::compare_by_title);
    std::cout << "Sorted by title:\n";
    for (auto s : songs) std::cout << s->title << "\n";

    Sorter::merge_sort(songs, Sorter::compare_by_duration_desc);
    std::cout << "Sorted by duration (desc):\n";
    for (auto s : songs) std::cout << s->title << " (" << s->duration << "s)\n";

    Sorter::merge_sort(songs, Sorter::compare_by_added_time);
    std::cout << "Sorted by added time:\n";
    for (auto s : songs) std::cout << s->title << "\n";

    // Snapshot and Analysis
    SnapshotExporter::export_snapshot(playlist, history, ratingTree);

    ArtistBlocker blocker;
    blocker.block_artist("Coldplay");
    std::cout << "Blocked artists:\n";
    blocker.display_blocklist();

    std::cout << "Duration analysis:\n";
    DurationAnalyzer::analyze(playlist);

    std::cout << "\n=== End of Demo ===\n";
    return 0;
}
