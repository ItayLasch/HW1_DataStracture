#ifndef GROUP_H
#define GROUP_H
#include "AVLTree.h"

class Group;

class Player
{
private:
    int player_id;
    int player_level;
    std::shared_ptr<Group> group_belonged;

public:
    Player():player_id(0),player_level(0),group_belonged(nullptr) {};
    Player(int player_id, int level, std::shared_ptr<Group> g_belong) : player_id(player_id), player_level(level), group_belonged(g_belong){};
    Player &operator=(const Player &) = default;
    int get_id()
    {
        return this->player_id;
    }

    int getLevel()
    {
        return this->player_level;
    }

    std::shared_ptr<Group> getGroup()
    {
        return this->group_belonged;
    }

    void SetLevel(int levelIncrease)
    {
        this->player_level += levelIncrease;
    }

    /*friend bool operator==(const Player &p, const int id);
    friend bool operator==(const Player &p1, const Player &p2);
    friend bool operator>(const Player &p, const int id);
    friend bool operator>(const Player &p1, const Player &p2);
    friend bool operator<(const Player &p, const int id);
    friend bool operator<(const Player &p1, const Player &p2);*/

    friend bool operator==(const Player &p, const int id)
    {
        return p.player_id == id;
    }

    friend bool operator>(const Player &p, const int id)
    {
        return p.player_id > id;
    }

    friend bool operator<(const Player &p, const int id)
    {
        return p.player_id < id;
    }

    friend bool operator==(const Player &p1, const Player &p2)
    {
        return (p1.player_id == p2.player_id && p1.player_level == p2.player_level);
    }

    friend bool operator>(const Player &p1, const Player &p2)
    {
        if (p1 < p2 || p1 == p2)
        {
            return false;
        }
        return true;
    }

    friend bool operator<(const Player &p1, const Player &p2)
    {
        int res = p1.player_level - p2.player_level;
        if (res < 0 || (res == 0 && p1.player_id < p2.player_id))
        {
            return true;
        }
        return false;
    }
};



class Group
{
private:
    int group_id;
    AVLTree<std::shared_ptr<Player>, Player> players_by_level;
    std::shared_ptr<Player> highest_level_player;

public:
    Group(int GroupID) : group_id(GroupID){};
    Group(int GroupID, AVLTree<std::shared_ptr<Player>, Player> players_tree, std::shared_ptr<Player> highest_level_player)
    {
        group_id = GroupID;
        players_by_level = players_tree;
        this->highest_level_player = highest_level_player;
    }

    ~Group() = default;

    int getId()
    {
        return this->group_id;
    }

    AVLTree<std::shared_ptr<Player>,Player> &getPlayersByLevel()
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

    friend bool operator==(const Group &g, const int id)
    {
        return g.group_id == id;
    }
    friend bool operator>(const Group &g, const int id){
        return g.group_id > id;
    }
    friend bool operator<(const Group &g, const int id){
        return g.group_id < id;
    }
};

/*bool operator==(const Group &g, const int id)
{
    return g.group_id == id;
}

bool operator>(const Group &g, const int id)
{
    return g.group_id > id;
}

bool operator<(const Group &g, const int id)
{
    return g.group_id < id;
}*/

#endif