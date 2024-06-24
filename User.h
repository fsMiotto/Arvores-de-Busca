#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

struct User {
    int id;
    std::string name;
    std::tm birthday;
};

bool isNull(User user){
    User userEmpty;
    return user.id == userEmpty.id && user.name == userEmpty.name;  
     //aqui eu não coloquei a comparação das datas pq a main não tem o compareDates e as 2 informações vazias já sao o suficiente para saber se é uma estrutura vazia
}

int compareDates(const std::tm& tm1, const std::tm& tm2) {
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));
    if (time1 > time2){ return 1; }
    else if (time1 < time2){ return -1; }
    else{ return 0; } // As datas são iguais
}


#endif  // USER_H