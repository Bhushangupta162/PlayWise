#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <ctime>

struct Song{
    std::string id;
    std::string title;
    std::string artist;
    int duration;
    std::time_t addedAt;

    Song(std::string _id,std::string _title,std::string _artist,int _duration)
    : id(_id),title(_title),artist(_artist),duration(_duration){
        addedAt = std::time(nullptr);
    }
};

#endif