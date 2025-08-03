#ifndef DURATION_ANALYZER_HPP
#define DURATION_ANALYZER_HPP

#include "Playlist.hpp"
#include <string>

class DurationAnalyzer {
public:
    static void analyze(const Playlist& playlist);
};

#endif
