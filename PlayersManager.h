#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H
#include "AVLTree.h"
#include "Group.h"
#include "Player.h"


class PlayersManager
{
    AVLTree<Group*> Groups;
    AVLTree<Player*> Players_by_ID;
    AVLTree<Player*> Players_by_Level;
    Player *Highest_ranked_player;

    public:
        PlayersManager();

        ~PlayersManager() = default;

        PlayersManager(const PlayersManager &other) = default;

        PlayersManager &operator=(const PlayersManager &other) = default;

        void AddGroup(int GroupID);

        void AddPlayer(int PlayerID, int GroupID, int Level);

        void RemovePlayer(int PlayerID);

        void ReplaceGroup(int GroupID, int ReplacementID);

        void IncreaseLevel(int PlayerID, int LevelIncrease);

        void GetHighestLevel(int GroupID, int *PlayerID);

        void GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
};




#endif