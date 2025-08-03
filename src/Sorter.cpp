#include "Sorter.hpp"

void Sorter::merge_sort(std::vector<Song*>& songs,
                        std::function<bool(Song*, Song*)> comp) {
    if (songs.size() <= 1) return;

    size_t mid = songs.size() / 2;
    std::vector<Song*> left(songs.begin(), songs.begin() + mid);
    std::vector<Song*> right(songs.begin() + mid, songs.end());

    merge_sort(left, comp);
    merge_sort(right, comp);

    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        songs[k++] = comp(left[i], right[j]) ? left[i++] : right[j++];
    }
    while (i < left.size()) songs[k++] = left[i++];
    while (j < right.size()) songs[k++] = right[j++];
}

// Comparators

bool Sorter::compare_by_title(Song* a, Song* b) {
    return a->title < b->title;
}

bool Sorter::compare_by_duration_asc(Song* a, Song* b) {
    return a->duration < b->duration;
}

bool Sorter::compare_by_duration_desc(Song* a, Song* b) {
    return a->duration > b->duration;
}

bool Sorter::compare_by_added_time(Song* a, Song* b) {
    return a->addedAt > b->addedAt; // newer first
}
