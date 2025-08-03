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
    std::cout << "=== 🎧 Welcome to PlayWise Demo ===\n\n";

    // ------------------------------
    // 1. Playlist Creation & Display
    // ------------------------------
    Playlist myPlaylist;

    myPlaylist.add_song("Imagine", "John Lennon", 183);
    myPlaylist.add_song("Bohemian Rhapsody", "Queen", 354);
    myPlaylist.add_song("Hey Jude", "The Beatles", 431);

    std::cout << "\n🎵 Initial Playlist:\n";
    myPlaylist.display();
    std::cout << "Playlist size: " << myPlaylist.size() << "\n";


    // ------------------------------
    // 2. Move Song (Hey Jude to top)
    // ------------------------------
    myPlaylist.move_song(2, 0);
    std::cout << "\n🔀 After Moving 'Hey Jude' to Top:\n";
    myPlaylist.display();
    std::cout << "Playlist size: " << myPlaylist.size() << "\n";


    // ------------------------------
    // 3. Reverse Playlist
    // ------------------------------
    myPlaylist.reverse_playlist();
    std::cout << "\n🔄 After Reversing Playlist:\n";
    myPlaylist.display();
    std::cout << "Playlist size: " << myPlaylist.size() << "\n";


    // ------------------------------
    // 4. Delete a Song (Index 1)
    // ------------------------------
    if (myPlaylist.size() > 1) {
        myPlaylist.delete_song(1);
        std::cout << "\n❌ After Deleting Song at Index 1:\n";
        myPlaylist.display();
    } else {
        std::cout << "\n⚠️ Skipped deletion: Not enough songs.\n";
    }
    std::cout << "Playlist size: " << myPlaylist.size() << "\n";


    // ------------------------------
    // 5. Playback History Integration
    // ------------------------------
    PlaybackHistory history(myPlaylist);

    std::cout << "\n▶️ Playing Songs...\n";
    if (myPlaylist.size() > 1) history.play_song(1);  // Play 2nd song
    if (myPlaylist.size() > 0) history.play_song(0);  // Play 1st song

    std::cout << "\n🎼 Playlist After Playing:\n";
    myPlaylist.display();

    std::cout << "\n🕘 Recently Played Songs:\n";
    history.display_history();

    // ------------------------------
    // 6. Undo Playback
    // ------------------------------
    std::cout << "\n⏪ Undo Last Played Song:\n";
    history.undo_last_play();

    std::cout << "\n🎼 Playlist After Undo:\n";
    myPlaylist.display();

    // ------------------------------
    // 7. Rating Tree Demo
    // ------------------------------
    std::cout << "\n🌟 Rating Tree Demo:\n";
    RatingTree ratingTree;

    ratingTree.insert_song(new Song(generateRandomId(), "Let It Be", "The Beatles", 243), 5);
    ratingTree.insert_song(new Song(generateRandomId(), "In the End", "Linkin Park", 4), 4);
    ratingTree.insert_song(new Song(generateRandomId(), "Lose Yourself", "Eminem", 5), 5);
    ratingTree.insert_song(new Song(generateRandomId(), "Fix You", "Coldplay", 3), 3);

    ratingTree.display();

    std::cout << "\n🔍 Search by Rating 5:\n";
    auto topRated = ratingTree.search_by_rating(5);
    for (auto s : topRated)
        std::cout << "- " << s->title << " by " << s->artist << "\n";

    std::cout << "\n❌ Delete one song from rating 5:\n";
    if (!topRated.empty()) {
        ratingTree.delete_song(topRated[0]->id);
    }

    std::cout << "\n🌲 Rating Tree After Deletion:\n";
    ratingTree.display();

    std::cout << "\n=== ✅ End of Demo ===\n";

    

    std::cout << "\n⚡ HashMap Lookup Demo:\n";

    SongIndex index;

    Song* s1 = new Song(generateRandomId(), "Blinding Lights", "The Weeknd", 201);
    Song* s2 = new Song(generateRandomId(), "Rolling in the Deep", "Adele", 228);

    index.add_song(s1);
    index.add_song(s2);
    index.display_index();

    std::cout << "\n🔍 Find by ID:\n";
    Song* found = index.find_by_id(s1->id);
    if (found)
        std::cout << "Found: " << found->title << " by " << found->artist << "\n";

    std::cout << "\n❌ Remove and Try Again:\n";
    index.remove_song(s1->id);
    Song* missing = index.find_by_id(s1->id);
    std::cout << (missing ? "Still Exists" : "Removed Successfully") << "\n";



    std::cout << "\n🔃 Sorting Demo:\n";

    std::vector<Song*> sampleSongs;
    sampleSongs.push_back(new Song(generateRandomId(), "Viva La Vida", "Coldplay", 242));
    sampleSongs.push_back(new Song(generateRandomId(), "Yesterday", "The Beatles", 145));
    sampleSongs.push_back(new Song(generateRandomId(), "One Dance", "Drake", 173));

    std::cout << "\nOriginal Order:\n";
    for (auto s : sampleSongs)
        std::cout << "- " << s->title << " (" << s->duration << "s)\n";

    Sorter::merge_sort(sampleSongs, Sorter::compare_by_title);
    std::cout << "\n🅰️ Sorted by Title:\n";
    for (auto s : sampleSongs)
        std::cout << "- " << s->title << " (" << s->duration << "s)\n";

    Sorter::merge_sort(sampleSongs, Sorter::compare_by_duration_desc);
    std::cout << "\n⏱️ Sorted by Duration (Descending):\n";
    for (auto s : sampleSongs)
        std::cout << "- " << s->title << " (" << s->duration << "s)\n";

    Sorter::merge_sort(sampleSongs, Sorter::compare_by_added_time);
    std::cout << "\n🕒 Sorted by Recently Added:\n";
    for (auto s : sampleSongs)
        std::cout << "- " << s->title << " (" << s->duration << "s)\n";


    // At end of demo
    SnapshotExporter::export_snapshot(myPlaylist, history, ratingTree);

    

    ArtistBlocker blocker;
    blocker.block_artist("Coldplay");

    std::cout << "\n🎯 Blocklist Demo:\n";
    blocker.display_blocklist();
    if (blocker.is_blocked("Coldplay")) {
        std::cout << "Blocked: Coldplay\n";
    }

    std::cout << "\n📏 Duration Analyzer:\n";
    DurationAnalyzer::analyze(myPlaylist);


    return 0;
}
