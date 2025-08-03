#ifndef SNAPSHOT_EXPORTER_HPP
#define SNAPSHOT_EXPORTER_HPP

#include "Song.hpp"
#include "Playlist.hpp"
#include "PlaybackHistory.hpp"
#include "RatingTree.hpp"
#include <vector>

class SnapshotExporter {
public:
    static void export_snapshot(const Playlist& playlist,
                                const PlaybackHistory& history,
                                const RatingTree& ratingTree);
};

#endif
