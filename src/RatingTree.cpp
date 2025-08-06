#include "RatingTree.hpp"
#include <iostream>
#include <functional>

RatingTree::RatingTree() : root(nullptr) {}

RatingTree::~RatingTree() {
    free_tree(root);
}

void RatingTree::free_tree(Node* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    for (auto* song : node->songs) delete song;
    delete node;
}

RatingTree::Node* RatingTree::insert(Node* node, Song* song, int rating) {
    if (!node) {
        Node* newNode = new Node(rating);
        newNode->songs.push_back(song);
        return newNode;
    }

    if (rating < node->rating)
        node->left = insert(node->left, song, rating);
    else if (rating > node->rating)
        node->right = insert(node->right, song, rating);
    else
        node->songs.push_back(song);

    return node;
}

void RatingTree::insert_song(Song* song, int rating) {
    root = insert(root, song, rating);
}

void RatingTree::search_by_rating(Node* node, int rating, std::vector<Song*>& result) const {
    if (!node) return;

    if (rating < node->rating)
        search_by_rating(node->left, rating, result);
    else if (rating > node->rating)
        search_by_rating(node->right, rating, result);
    else
        result = node->songs;
}

std::vector<Song*> RatingTree::search_by_rating(int rating) const {
    std::vector<Song*> result;
    search_by_rating(root, rating, result);
    return result;
}

RatingTree::Node* RatingTree::delete_song(Node* node, const std::string& song_id) {
    if (!node) return nullptr;

    node->left = delete_song(node->left, song_id);
    node->right = delete_song(node->right, song_id);

    auto& list = node->songs;
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->id == song_id) {
            delete *it;
            list.erase(it);
            break;
        }
    }
    return node;
}

void RatingTree::delete_song(const std::string& song_id) {
    root = delete_song(root, song_id);
}

void RatingTree::display() {
    std::function<void(Node*)> inorder = [&](Node* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << "Rating " << node->rating << ":\n";
        for (auto* s : node->songs)
            std::cout << "- " << s->title << " by " << s->artist << "\n";
        inorder(node->right);
    };
    inorder(root);
}
