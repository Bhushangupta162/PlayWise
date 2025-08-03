# PlayWise 🎵

A C++-based smart playlist management engine designed for real-time music organization and recommendation. Built using advanced data structures like Linked Lists, Stacks, Binary Search Trees, HashMaps, and Merge Sort, PlayWise serves as the intelligent backend of a personalized music experience platform.

---

## 🚀 Features

### Core Modules

* **Playlist Engine**: Doubly linked list supporting song addition, deletion, movement, and lazy reversal.
* **Playback History**: Stack-based undo system to requeue previously played songs.
* **Song Rating Tree**: Binary Search Tree storing songs grouped by user ratings (1–5).
* **Instant Lookup**: HashMap for O(1) retrieval by song ID or title.
* **Sorting Engine**: Merge sort to sort playlists by title, duration, or recently added time.

### Specialized Modules

* **Artist Blocklist**: Prevent songs by specific artists from being added or played.
* **Duration Visualizer**: Compute total, max, and min song durations in a playlist.
* **System Snapshot**: Export live stats: top 5 longest songs, recently played stack, rating-wise song count.

---

## 📂 Project Structure

```bash
playwise/
├── include/                 # Header files
├── src/                     # Implementations
├── tests/                   # Unit tests
├── build/                  # Build output (gitignored)
├── CMakeLists.txt          # Build configuration
├── README.md               # Project description
└── TECHNICAL_DESIGN.md     # Design document (optional)
```

---

## ⚙️ Build & Run

### Prerequisites

* CMake >= 3.10
* g++ / clang++ with C++17 support

### Steps

```bash
mkdir build && cd build
cmake ..
mingw32-make           # or just 'make' on Linux/Mac
./playwise             # run main application
./test_playwise        # run all unit tests
```

---

## 📊 Unit Test Coverage

* `Playlist` (add, delete, move, reverse)
* `PlaybackHistory` (push, undo)
* `RatingTree` (insert, search, delete)
* `HashMap Index` (insert, find, remove)
* `Sorter` (title, duration ascending/descending)
* `ArtistBlocker` (block, unblock, check)
* `DurationAnalyzer` (total, min, max)

---

## 📅 Future Enhancements

* Song priority queues for smart playback
* User session system
* LLM-driven recommendation integration
* Export/import playlists to file