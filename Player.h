#ifndef PLAYER_H
#define PLAYER_H
#include "Group.h"

class Player
{
    int player_id;
    int player_level;
    Group *group_belonged;

    public:
        Player(int player_id, int level, Group *g_belong) : player_id(player_id), player_level(level), group_belonged(g_belong){};

        int getid()
        {
            return this->player_id;
    }

    int getLevel(){
        return this->player_level;
    }


};  
#endif