#ifndef GROUP_H
#define GROUP_H
#include "AVLTree.h"

class Group;
class PlayerKey;

class Player
{
private:
    int player_id;
    int player_level;
    std::shared_ptr<Group> group_belonged;

public:
    Player() : player_id(0), player_level(0), group_belonged(nullptr){};
    ~Player()
    {
        this->group_belonged = nullptr;
    }
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

    void SetGroup(std::shared_ptr<Group> g)
    {
        this->group_belonged = g;
    }

    void SetLevel(int levelIncrease)
    {
        this->player_level += levelIncrease;
    }

};

class Group
{
private:
    int group_id;
    AVLTree<std::shared_ptr<Player>, PlayerKey> players_by_level;
    std::shared_ptr<Player> highest_level_player;

public:
    Group(int GroupID) : group_id(GroupID){};
    Group(int GroupID, AVLTree<std::shared_ptr<Player>, PlayerKey> players_tree, std::shared_ptr<Player> highest_level_player)
    {
        group_id = GroupID;
        players_by_level = players_tree;
        this->highest_level_player = highest_level_player;
    }

    ~Group()
    {
       /* this->players_by_level.Inorder([&](std::shared_ptr<Player> p)
                                       { p->SetGroup(nullptr); });*/
        this->highest_level_player = nullptr;
    }

    int getId()
    {
        return this->group_id;
    }

    AVLTree<std::shared_ptr<Player>, PlayerKey> &getPlayersByLevel()
    {
        return this->players_by_level;
    }

    std::shared_ptr<Player> GetHighestRanked()
    {
        return this->highest_level_player;
    }

    static void updateGroupTree(std::shared_ptr<Group> curr,AVLTree<std::shared_ptr<Player>, PlayerKey> &mergeTree)
    {
        curr->players_by_level = mergeTree;
        curr->highest_level_player = mergeTree.FindMax();
        curr->players_by_level.Inorder([&](std::shared_ptr<Player> p)
                                       {
        if(p->getGroup()->getId() != curr->group_id)
        {
            p->SetGroup(curr);
        } });
    }

    void SetHighestRanked(std::shared_ptr<Player> player)
    {
        this->highest_level_player = player;
    }
};

class PlayerKey
{
    int player_id;
    int player_level;

public:
    PlayerKey() : player_id(-1), player_level(-1){};
    PlayerKey(int id, int level) : player_id(id), player_level(level){};
    ~PlayerKey() = default;
    PlayerKey(const PlayerKey &other) = default;
    PlayerKey &operator=(const PlayerKey &other) = default;
    void ChangeLevel(int newLevel)
    {
        this->player_level = newLevel;
    }

    friend bool operator==(const PlayerKey &p1, const PlayerKey &p2)
    {
        return (p1.player_id == p2.player_id && p1.player_level == p2.player_level);
    }

    friend bool operator>(const PlayerKey &p1, const PlayerKey &p2)
    {
        if (p1 < p2 || p1 == p2)
        {
            return false;
        }
        return true;
    }

    friend bool operator<(const PlayerKey &p1, const PlayerKey &p2)
    {
        int res = p1.player_level - p2.player_level;
        if (res < 0 || (res == 0 && p1.player_id < p2.player_id))
        {
            return true;
        }
        return false;
    }
};

#endif