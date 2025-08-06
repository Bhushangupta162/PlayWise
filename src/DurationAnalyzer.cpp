#include "DurationAnalyzer.hpp"
#include <iostream>
#include <climits>

void DurationAnalyzer::analyze(const Playlist& playlist) {
    int total = 0;
    int minDur = INT_MAX;
    int maxDur = INT_MIN;
    std::string minSong, maxSong;

    playlist.for_each([&](Song* s) {
        total += s->duration;
        if (s->duration < minDur) {
            minDur = s->duration;
            minSong = s->title;
        }
        if (s->duration > maxDur) {
            maxDur = s->duration;
            maxSong = s->title;
        }
    });

    std::cout << "\n Playlist Duration Summary:\n";
    std::cout << "- Total Duration: " << total << " seconds\n";
    std::cout << "- Longest: " << maxSong << " (" << maxDur << "s)\n";
    std::cout << "- Shortest: " << minSong << " (" << minDur << "s)\n";
}
