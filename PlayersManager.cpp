#include "PlayersManager.h"

PlayersManager::PlayersManager()
{
    this->Groups = AVLTree<Group*>();
    this->Players_by_ID = AVLTree<Player*>();
    this->Players_by_Level = AVLTree<Player*>();
    this->Highest_ranked_player = nullptr;
}

void PlayersManager::AddGroup(int GroupID)
{
    if (this->Groups.isExists(GroupID) == false)
    {
        return;
    }

    Group *newGroup = new Group(GroupID);
    if(newGroup == nullptr)
    {
        return;
    }

    this->Groups.AddItem(newGroup);
}

void PlayersManager::AddPlayer(int PlayerID, int GroupID, int Level)
{
    if(this->Groups.isExists(GroupID) == false)
    {
        return;
    }

    Group* g = this->Groups.getData(GroupID);
    if(g->getPlayersByID().isExists(PlayerID))
    {
        return;
    }

    Player *newP = new Player(PlayerID, Level, g);
    g->getPlayersByID().AddItem(newP);
    g->getPlayersByLevel().AddItem(newP);

    if(Level > this->Highest_ranked_player->getLevel())
    {
        this->Highest_ranked_player = newP;
    }

    if(Level > g->GetHighestRanked()->getLevel())
    {
        g->SetHighestRanked(newP);
    }
}
