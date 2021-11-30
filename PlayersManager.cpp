#include "PlayersManager.h"

PlayersManager::PlayersManager()
{
    this->Groups = AVLTree<std::shared_ptr<Group>>();
    this->Players_by_ID = AVLTree<std::shared_ptr<Player>>();
    this->Players_by_Level = AVLTree<std::shared_ptr<Player>>();
    this->Filled_Groups = AVLTree<std::shared_ptr<Group>>();
    this->Highest_ranked_player = nullptr;
}

void PlayersManager::AddGroup(int GroupID)
{
    if (this->Groups.isExists(GroupID) == false)
    {
        throw GroupNotExist();
    }

    std::shared_ptr<Group> newGroup(new Group(GroupID));
    if (newGroup == nullptr)
    {
        throw NullArg();
    }

    this->Groups.AddItem(newGroup, GroupID);
}

void PlayersManager::AddPlayer(int PlayerID, int GroupID, int Level)
{
    if (this->Groups.isExists(GroupID) == false)
    {
        throw GroupNotExist();
    }

    if (this->Players_by_ID.isExists(PlayerID))
    {
        throw PlayerExist();
    }

    std::shared_ptr<Group> g = this->Groups.getData(GroupID);
    std::shared_ptr<Player> newP(new Player(PlayerID, Level, g));
    g->getPlayersByLevel().AddItem(newP, newP);
    this->Players_by_ID.AddItem(newP, PlayerID);
    this->Players_by_Level.AddItem(newP, newP);

    if (Level > this->Highest_ranked_player->getLevel())
    {
        this->Highest_ranked_player = newP;
    }

    if (Level > g->GetHighestRanked()->getLevel())
    {
        g->SetHighestRanked(newP);
    }

    if(g->getPlayersByLevel().getSize() == 1)
    {
        this->Filled_Groups.AddItem(g, GroupID);
    }
}

void PlayersManager::RemovePlayer(int PlayerID)
{
    if (this->Players_by_ID.isExists(PlayerID) == false)
    {
        throw PlayerNotExsist();
    }

    std::shared_ptr<Player> player_removed = this->Players_by_ID.getData(PlayerID);
    std::shared_ptr<Group> group_player = player_removed->getGroup();

    //remove from player_by_level
    this->Players_by_Level.removeItem(player_removed);
    if (player_removed == this->Highest_ranked_player)
    {
        this->Highest_ranked_player = this->Players_by_Level.FindMax();
    }

    //remove from group
    group_player->getPlayersByLevel().removeItem(player_removed); 
    if (player_removed == group_player->GetHighestRanked())
    {
        group_player->SetHighestRanked(group_player->getPlayersByLevel().FindMax());
    }
    //remove from player_by_ID
    this->Players_by_ID.removeItem(PlayerID);

    //check if group is empty
    if(group_player->getPlayersByLevel().getSize() == 0)
    {
        this->Filled_Groups.removeItem(group_player->getId());
    }
}

void PlayersManager::ReplaceGroup(int GroupID, int ReplacementID)
{
    if (!this->Groups.isExists(GroupID) || !this->Groups.isExists(ReplacementID))
    {
        throw GroupNotExist();
    }

    std::shared_ptr<Group> currGroup = this->Groups.getData(GroupID);
    std::shared_ptr<Group> repGroup = this->Groups.getData(ReplacementID);

    AVLTree<std::shared_ptr<Player>>::TransferItems(currGroup->getPlayersByLevel().getRoot(), repGroup->getPlayersByLevel());
    this->Groups.removeItem(currGroup->getId());
}

void PlayersManager::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    if (this->Players_by_ID.isExists(PlayerID) == false)
    {
        throw PlayerNotExsist();
    }

    std::shared_ptr<Player> p = this->Players_by_ID.getData(PlayerID);
    std::shared_ptr<Group> g = p->getGroup();
    this->Players_by_Level.removeItem(PlayerID); 
    g->getPlayersByLevel().removeItem(PlayerID);
    p->SetLevel(LevelIncrease);
    if (p->getLevel() > this->Highest_ranked_player->getLevel())
    {
        this->Highest_ranked_player = p;
    }
    if (p->getLevel() > g->GetHighestRanked()->getLevel())
    {
        g->SetHighestRanked(p);
    }
    this->Players_by_Level.AddItem(p, p);
    g->getPlayersByLevel().AddItem(p, p);
}

int PlayersManager::GetHighestLevel(int GroupID)
{
    if (GroupID < 0)
    {
        if (this->Players_by_ID.getSize() == 0)
        {
            return -1;
        }
        else
        {
            return Highest_ranked_player->get_id();
        }
    }

    if (this->Groups.isExists(GroupID) == false)
    {
        throw GroupNotExist();
    }

    std::shared_ptr<Group> group = this->Groups.getData(GroupID);
    if (!group)
    {
        throw NullArg();
    }

    if (group->getPlayersByLevel().getSize() == 0)
    {
        return -1;
    }

    return group->GetHighestRanked()->get_id();
}

void PlayersManager::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers){
    if(this == nullptr){
        throw NullArg();
    }
    int i = 0;
    std::shared_ptr<Group> g = this->Groups.getData(GroupID);
    if(GroupID < 0){
        *numOfPlayers = this->Players_by_Level.getSize();
    }
    else if(!this->Groups.isExists(GroupID)){
        throw GroupNotExist();
    }
    else{
        *numOfPlayers = g->getPlayersByLevel().getSize();
    }

    if(*numOfPlayers == 0){
        Players = nullptr;
        return;
    }
    std::shared_ptr<Player> *tempArr = new std::shared_ptr<Player>[*numOfPlayers];
    if(GroupID < 0){
        this->Players_by_Level.inOrderToArray(tempArr, *numOfPlayers);
    }
    else{
        g->getPlayersByLevel().inOrderToArray(tempArr, *numOfPlayers);
    }
    for (int i = 0; i < *numOfPlayers; i++)
    {
        *(Players[i]) = (tempArr[i]->get_id());
    }
    delete tempArr;
}


void PlayersManager::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    if(this->Filled_Groups.getSize() < numOfGroups){
        throw NotEnoughGroups();
    }

    std::shared_ptr<Group> *tempArr = new std::shared_ptr<Group>[numOfGroups];
    this->Filled_Groups.inOrderToArray(tempArr, numOfGroups);
    for (int i = 0; i < numOfGroups; i++)
    {
        *(Players[i]) = tempArr[i]->GetHighestRanked()->get_id();
    }
    delete tempArr;
    
}

void PlayersManager::Quit()
{
    this->~PlayersManager();
}
