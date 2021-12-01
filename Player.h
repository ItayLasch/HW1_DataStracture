/*#ifndef PLAYER_H
#define PLAYER_H
#include "Group.h"

class Player
{
private:
    int player_id;
    int player_level;
    std::shared_ptr<Group> group_belonged;

public:
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

    friend bool operator==(const Player &p, const int id);
    friend bool operator==(const Player &p1, const Player &p2);
    friend bool operator>(const Player &p, const int id);
    friend bool operator>(const Player &p1, const Player &p2);
    friend bool operator<(const Player &p, const int id);
    friend bool operator<(const Player &p1, const Player &p2);

    /*
        bool operator<(const int id)
        {
            return player_id < id;
        }

        bool operator>(const int id)
        {
            return player_id > id;
        }

        bool operator<(const Player *other)
        {
            int res = this->player_level - other->player_level;
            if (res > 0 || (res == 0 && this->player_id > other->player_id))
                return true;
            return false;
        }

        bool operator>(const Player *other)
        {
            if (this < other || this == other)
            {
                return false;
            }
            return true;
        }

        bool operator==(const Player *other)
        {
            return (this->player_id == other->player_id && this->player_level == other->player_level);
        }
};

bool operator==(const Player &p, const int id)
{
    return p.player_id == id;
}

bool operator>(const Player &p, const int id)
{
    return p.player_id > id;
}
bool operator<(const Player &p, const int id)
{
    return p.player_id < id;
}

bool operator==(const Player &p1, const Player &p2)
{
    return (p1.player_id == p2.player_id && p1.player_level == p2.player_level);
}

bool operator>(const Player &p1, const Player &p2)
{
    if (p1 < p2 || p1 == p2)
    {
        return false;
    }
    return true;
}

bool operator<(const Player &p1, const Player &p2)
{
    int res = p1.player_level - p2.player_level;
    if (res > 0 || (res == 0 && p1.player_id > p2.player_id))
        return true;
    return false;
}

#endif*/