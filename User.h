#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

struct User {
    int id;
    std::string name;
    std::tm birthday;
};

#endif  // USER_H