#ifndef SORTER_HPP
#define SORTER_HPP

#include "Song.hpp"
#include <vector>
#include <functional>

class Sorter {
public:
    static void merge_sort(std::vector<Song*>& songs,
                           std::function<bool(Song*, Song*)> comp);

    static bool compare_by_title(Song* a, Song* b);
    static bool compare_by_duration_asc(Song* a, Song* b);
    static bool compare_by_duration_desc(Song* a, Song* b);
    static bool compare_by_added_time(Song* a, Song* b);
};

#endif
