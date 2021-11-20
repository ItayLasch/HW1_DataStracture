#ifndef GROUP_H
#define GROUP_H
#include "AVLTree.h"
#include "Player.h"

class Group
{
    int group_id;
    AVLTree<Player*> players_by_id;
    AVLTree<Player*> players_by_level;
    Player *highest_level_player;

    public:
        Group(int GroupID){
            this->group_id = GroupID;
            this->players_by_id = AVLTree<Player*>();
            this->players_by_level = AVLTree<Player*>();
            this->highest_level_player = nullptr;
        }

        int getId()
        {
            return this->group_id;
        }

        AVLTree<Player*>& getPlayersByID()
        {
            return players_by_id;
        }

        AVLTree<Player*> &getPlayersByLevel()
        {
            return players_by_level;
        }

        Player* GetHighestRanked()
        {
            return this->highest_level_player;
        }

        void SetHighestRanked(Player* player)
        {
             this->highest_level_player = player;
        }
};

#endif