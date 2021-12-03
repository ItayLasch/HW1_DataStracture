#include "PlayersManager.h"

PlayersManager::PlayersManager()
{
    this->Players_by_ID = AVLTree<std::shared_ptr<Player>, int>();
    this->Players_by_Level = AVLTree<std::shared_ptr<Player>, PlayerKey>();
    this->Groups = AVLTree<std::shared_ptr<Group>, int>();
    this->Filled_Groups = AVLTree<std::shared_ptr<Group>, int>();
    this->Highest_ranked_player = nullptr;
}

PlayersManager::~PlayersManager()
{
    this->Players_by_ID.Inorder([&](std::shared_ptr<Player> p)
                                {   
        if(p->getGroup() != nullptr)
        {
            p->getGroup().reset();
            p->SetGroup(nullptr);
        } });

    this->Highest_ranked_player.reset();
    this->Highest_ranked_player = nullptr;
}

void PlayersManager::AddGroup(int GroupID)
{
    if (this->Groups.isExists(GroupID))
    {
        throw GroupExist();
    }

    std::shared_ptr<Group> newGroup(new Group(GroupID));
    if (newGroup == nullptr)
    {
        throw NullArg();
    }

    this->Groups.AddItem(newGroup, GroupID);
    newGroup.reset();
    newGroup = nullptr;
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
    PlayerKey p_key = PlayerKey(PlayerID, Level);
    g->getPlayersByLevel().AddItem(newP, p_key);
    this->Players_by_ID.AddItem(newP, PlayerID);
    this->Players_by_Level.AddItem(newP, p_key);

    if (this->Highest_ranked_player == nullptr || Level > this->Highest_ranked_player->getLevel())
    {
        this->Highest_ranked_player = newP;
    }

    if (g->GetHighestRanked() == nullptr || Level > g->GetHighestRanked()->getLevel())
    {
        g->SetHighestRanked(newP);
    }

    if (g->getPlayersByLevel().getSize() == 1)
    {
        this->Filled_Groups.AddItem(g, GroupID);
    }

    newP.reset();
    newP = nullptr;
}

void PlayersManager::RemovePlayer(int PlayerID)
{
    if (this->Players_by_ID.isExists(PlayerID) == false)
    {
        throw PlayerNotExsist();
    }

    std::shared_ptr<Player> player_removed = this->Players_by_ID.getData(PlayerID);
    std::shared_ptr<Group> group_player = player_removed->getGroup();

    PlayerKey pkey = PlayerKey(player_removed->get_id(), player_removed->getLevel());
    // remove from player_by_level
    this->Players_by_Level.removeItem(pkey);
    if (player_removed == this->Highest_ranked_player)
    {
        if (this->Players_by_Level.getSize() == 0)
        {
            this->Highest_ranked_player = nullptr;
        }
        else
        {
            this->Highest_ranked_player = this->Players_by_Level.FindMax();
        }
    }

    // remove from group
    group_player->getPlayersByLevel().removeItem(pkey);
    if (player_removed == group_player->GetHighestRanked())
    {
        if (group_player->getPlayersByLevel().getSize() == 0)
        {
            group_player->SetHighestRanked(nullptr);
        }
        else
        {
            group_player->SetHighestRanked(group_player->getPlayersByLevel().FindMax());
        }
    }

    // remove from player_by_ID
    this->Players_by_ID.removeItem(PlayerID);

    // check if group is empty
    if (group_player->getPlayersByLevel().getSize() == 0)
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

    std::shared_ptr<Group> group_to_delete = this->Groups.getData(GroupID);
    std::shared_ptr<Group> replace_group = this->Groups.getData(ReplacementID);
    AVLTree<std::shared_ptr<Player>, PlayerKey> *mergeTree = new AVLTree<std::shared_ptr<Player>, PlayerKey>();
    AVLTree<std::shared_ptr<Player>, PlayerKey>::AVLTreeMerge(group_to_delete->getPlayersByLevel(), replace_group->getPlayersByLevel(), *mergeTree);

    if (group_to_delete->getPlayersByLevel().getSize() != 0)
    {
        this->Filled_Groups.removeItem(group_to_delete->getId());
    }
    this->Groups.removeItem(group_to_delete->getId());

    Group::updateGroupTree(replace_group, *mergeTree);
    delete mergeTree;
    replace_group->getPlayersByLevel().Inorder([&](std::shared_ptr<Player> p)
                                               {
        if(p->getGroup()->getId() != replace_group->getId())
        {
            p->SetGroup(replace_group);
        } });
    return;
}

void PlayersManager::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    if (this->Players_by_ID.isExists(PlayerID) == false)
    {
        throw PlayerNotExsist();
    }

    std::shared_ptr<Player> p = this->Players_by_ID.getData(PlayerID);
    std::shared_ptr<Group> g = p->getGroup();
    PlayerKey pKey(p->get_id(), p->getLevel());
    this->Players_by_Level.removeItem(pKey);
    g->getPlayersByLevel().removeItem(pKey);
    p->SetLevel(LevelIncrease);
    pKey.ChangeLevel(p->getLevel());

    if (p->getLevel() > this->Highest_ranked_player->getLevel())
    {
        this->Highest_ranked_player = p;
    }
    if (p->getLevel() > g->GetHighestRanked()->getLevel())
    {
        g->SetHighestRanked(p);
    }
    this->Players_by_Level.AddItem(p, pKey);
    g->getPlayersByLevel().AddItem(p, pKey);
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

void PlayersManager::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    std::shared_ptr<Group> g = this->Groups.getData(GroupID);
    if (GroupID < 0)
    {
        *numOfPlayers = this->Players_by_Level.getSize();
    }
    else if (!this->Groups.isExists(GroupID))
    {
        throw GroupNotExist();
    }
    else
    {
        *numOfPlayers = g->getPlayersByLevel().getSize();
    }

    if (*numOfPlayers == 0)
    {
        *Players = NULL;
        return;
    }

    int *ret_arr = (int *)malloc(sizeof(int) * (*numOfPlayers));
    if (!(ret_arr))
    {
        throw std::bad_alloc();
    }
    std::shared_ptr<Player> *tempArrData = new std::shared_ptr<Player>[*numOfPlayers];
    PlayerKey *tempArrKey = new PlayerKey[*numOfPlayers];
    if (GroupID < 0)
    {
        this->Players_by_Level.inOrderToArrays(tempArrData, tempArrKey, *numOfPlayers);
    }
    else
    {
        g->getPlayersByLevel().inOrderToArrays(tempArrData, tempArrKey, *numOfPlayers);
    }

    for (int i = 0; i < *numOfPlayers; i++)
    {
        ret_arr[i] = (tempArrData[i]->get_id());
    }

    delete[] tempArrKey;
    delete[] tempArrData;
    *Players = ret_arr;
}

void PlayersManager::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    if(Players == nullptr)
    {
        throw NullArg();
    }

    if (this->Filled_Groups.getSize() < numOfGroups)
    {
        throw NotEnoughGroups();
    }

    int *ret_arr = (int *)malloc(sizeof(int) * (numOfGroups));
    if (!(ret_arr))
    {
        throw std::bad_alloc();
    }
    std::shared_ptr<Group> *tempArrData = new std::shared_ptr<Group>[numOfGroups];
    int *tempArrKey = new int[numOfGroups];
    this->Filled_Groups.inOrderToArrays(tempArrData, tempArrKey, numOfGroups);
    for (int i = 0; i < numOfGroups; i++)
    {
        ret_arr[i] = tempArrData[i]->getPlayersByLevel().FindMax()->get_id();
    }

    delete[] tempArrData;
    delete[] tempArrKey;
    *Players = ret_arr;
    /*int i = 0;
    this->Filled_Groups.Inorder([&](std::shared_ptr<Group> g)
                                {
        if(i == numOfGroups)
        {
            return;
        }

        (*Players)[i] = g->getPlayersByLevel().FindMax()->get_id();
        i++; });

    if (i < numOfGroups)
    {
        return;
    }*/
}

void PlayersManager::Quit(PlayersManager *PM)
{
    delete PM;
    return;
}
