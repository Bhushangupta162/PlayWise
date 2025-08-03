#ifndef RATING_TREE_HPP
#define RATING_TREE_HPP

#include "Song.hpp"
#include <vector>
#include <string>

class RatingTree {
private:
    struct Node {
        int rating;
        std::vector<Song*> songs;
        Node* left;
        Node* right;

        Node(int r) : rating(r), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, Song* song, int rating);
    Node* delete_song(Node* node, const std::string& song_id);
    void search_by_rating(Node* node, int rating, std::vector<Song*>& result)const;
    void free_tree(Node* node);

public:
    RatingTree();
    ~RatingTree();

    void insert_song(Song* song, int rating);
    std::vector<Song*> search_by_rating(int rating) const;
    void delete_song(const std::string& song_id);

    void display(); // Optional: print entire tree
};

#endif
