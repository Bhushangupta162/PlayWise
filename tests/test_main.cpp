#include <iostream>
#include <cassert>
#include <vector>
#include "../include/Playlist.hpp"
#include "../include/utils.hpp"
#include "../include/Sorter.hpp"
#include "../include/RatingTree.hpp"
#include "../include/SongIndex.hpp"
#include "../include/PlaybackHistory.hpp"
#include "../include/ArtistBlocker.hpp"
#include "../include/DurationAnalyzer.hpp"

void test_add_song() {
    Playlist p;
    p.add_song("Test Song", "Test Artist", 120);
    int count = 0;
    p.for_each([&](Song* s) {
        assert(s->title == "Test Song");
        assert(s->artist == "Test Artist");
        assert(s->duration == 120);
        count++;
    });
    assert(count == 1);
    std::cout << "✅ test_add_song passed.\n";
}

void test_sort_by_duration() {
    std::vector<Song*> songs;
    songs.push_back(new Song("id1", "A", "Artist1", 240));
    songs.push_back(new Song("id2", "B", "Artist2", 180));
    songs.push_back(new Song("id3", "C", "Artist3", 300));

    Sorter::merge_sort(songs, Sorter::compare_by_duration_asc);
    assert(songs[0]->duration == 180);
    assert(songs[2]->duration == 300);
    std::cout << "✅ test_sort_by_duration passed.\n";
}

void test_rating_tree() {
    RatingTree tree;
    tree.insert_song(new Song("id1", "X", "Artist1", 200), 5);
    tree.insert_song(new Song("id2", "Y", "Artist2", 210), 5);

    auto songs = tree.search_by_rating(5);
    assert(songs.size() == 2);

    tree.delete_song("id1");
    auto songs2 = tree.search_by_rating(5);
    assert(songs2.size() == 1);
    std::cout << "✅ test_rating_tree passed.\n";
}

void test_song_index() {
    SongIndex index;
    Song* s1 = new Song("idA", "Alpha", "ArtistA", 100);
    index.add_song(s1);

    Song* found = index.find_by_id("idA");
    assert(found != nullptr);
    assert(found->title == "Alpha");

    index.remove_song("idA");
    assert(index.find_by_id("idA") == nullptr);
    std::cout << "✅ test_song_index passed.\n";
}

void test_playback_history() {
    Playlist p;
    p.add_song("S1", "A1", 100);
    p.add_song("S2", "A2", 120);
    PlaybackHistory hist(p);

    hist.play_song(1);  // removes "S2"
    hist.play_song(0);  // removes "S1"
    hist.undo_last_play(); // re-adds "S1"

    int count = 0;
    p.for_each([&](Song*) { count++; });
    assert(count == 1);  // ✅ Only one undone
    std::cout << "✅ test_playback_history passed.\n";
}


void test_artist_blocker() {
    ArtistBlocker ab;
    ab.block_artist("BlockedArtist");
    assert(ab.is_blocked("BlockedArtist"));
    ab.unblock_artist("BlockedArtist");
    assert(!ab.is_blocked("BlockedArtist"));
    std::cout << "✅ test_artist_blocker passed.\n";
}

void test_duration_analyzer() {
    Playlist p;
    p.add_song("Short", "A", 100);
    p.add_song("Long", "B", 300);
    // Just run to ensure it executes
    DurationAnalyzer::analyze(p);
    std::cout << "✅ test_duration_analyzer executed.\n";
}

int main() {
    std::cout << "\n🔬 Running All PlayWise Unit Tests...\n";
    test_add_song();
    test_sort_by_duration();
    test_rating_tree();
    test_song_index();
    test_playback_history();
    test_artist_blocker();
    test_duration_analyzer();
    std::cout << "\n✅ All tests completed successfully.\n";
    return 0;
}
