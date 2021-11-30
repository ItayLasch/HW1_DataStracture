#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H
#include "AVLTree.h"
#include "Group.h"
#include "Player.h"
#include "Exceptions.h"

class PlayersManager
{
    AVLTree<std::shared_ptr<Group>> Groups;
    AVLTree<std::shared_ptr<Player>> Players_by_ID;
    AVLTree<std::shared_ptr<Player>> Players_by_Level;
    AVLTree<std::shared_ptr<Group>> Filled_Groups;
    std::shared_ptr<Player> Highest_ranked_player;

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

    int GetHighestLevel(int GroupID);

    void GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);

    void GetGroupsHighestLevel(int numOfGroups, int **Players);

    void Quit();
};  

#endif