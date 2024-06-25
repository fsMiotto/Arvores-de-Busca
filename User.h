#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

//estrutura de usuarios
struct User {
    int id;
    std::string name;
    std::tm birthday;
};

//metodo para comparar datas tm, enviado pelo monitor e adaptado no return
inline int compareDates(const std::tm& tm1, const std::tm& tm2) {
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));
    if (time1 > time2){ return 1; }
    else if (time1 < time2){ return -1; }
    else{ return 0; } // As datas são iguais
}

//verifica se a estrutura sem valores nulos nos campos, ou seja, se é null
inline bool isNull(User user){
    User userEmpty;
    return user.id == userEmpty.id && user.name == userEmpty.name && compareDates(user.birthday, userEmpty.birthday) == 0;  
}



#endif  // USER_H