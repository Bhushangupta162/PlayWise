#include "utils.hpp"
#include <random>
#include <sstream>

std::string generateRandomId(){
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        int len=8;
        std:: stringstream ss;
        std:: random_device rd;
        std:: mt19937 rng(rd());
        for(int i=0;i<len;i++){
            ss << alphanum[rng() % (sizeof(alphanum)-1)];
        }
        return ss.str();
}