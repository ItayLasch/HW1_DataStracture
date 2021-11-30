#ifndef GROUP_H
#define GROUP_H
#include "AVLTree.h"
#include "Player.h"

class Group
{
    int group_id;
    AVLTree<std::shared_ptr<Player>> players_by_level;
    std::shared_ptr<Player> highest_level_player;

public:
    Group(int GroupID) : group_id(GroupID){};

    ~Group() = default;

    int getId()
    {
        return this->group_id;
    }

    AVLTree<std::shared_ptr<Player>> &getPlayersByLevel()
    {
        return this->players_by_level;
    }

    std::shared_ptr<Player> GetHighestRanked()
    {
        return this->highest_level_player;
    }

    void SetHighestRanked(std::shared_ptr<Player> player)
    {
            this->highest_level_player = player;
    }
        
    bool operator==(const int id)
    {
        return group_id == id;
    }

    bool operator<(const int id){
        return group_id < id;
    }

    bool operator>(const int id){
        return group_id > id;
    }
};

#endif