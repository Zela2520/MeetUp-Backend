#pragma once

#include <string>
#include <map>

#include "user.h"
#include "day.h"

class Group {
private:
    std::string group_id;
    std::map <int, User> group_map;
    Day day;
public:
    Group();
    
    Group AddUser();

    Group DeleteUser();

    int Size();

    Group GetGropup();
};