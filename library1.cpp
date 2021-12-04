#include "library1.h"
#include "PlayersManager.h"


void *Init()
{
    PlayersManager *DS = new PlayersManager();
    return (void *)DS;
}

StatusType AddGroup(void *DS, int GroupID)
{
    if(DS == NULL || GroupID <= 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((PlayersManager *)DS)->AddGroup(GroupID);
    }
    catch (GroupExist &e)
    {
        return FAILURE;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(...)
    {
        return UNKNOWN_ERROR;
    }
    return SUCCESS;
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level)
{
    if(DS == NULL || GroupID <= 0 || PlayerID <= 0 || Level < 0)
    {
        return INVALID_INPUT;
    }

    try {
        ((PlayersManager *)DS)->AddPlayer(PlayerID, GroupID, Level);
    }
    catch(GroupNotExist &e)
    {
        return FAILURE;
    }
    catch (PlayerExist &e)
    {
        return FAILURE;
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS == NULL || PlayerID <= 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((PlayersManager *)DS)->RemovePlayer(PlayerID);
    }
    catch(PlayerNotExsist &e)
    {
        return FAILURE;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
{
    if(DS == NULL || GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID )
    {
        return INVALID_INPUT;
    }

    try
    {
        ((PlayersManager *)DS)->ReplaceGroup(GroupID, ReplacementID);
    }
    catch(GroupNotExist & e)
    {
        return FAILURE;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS == NULL || PlayerID <= 0 || LevelIncrease <= 0)
    {
        return INVALID_INPUT;
    }

    try
    {
        ((PlayersManager *)DS)->IncreaseLevel(PlayerID, LevelIncrease);
    }
    catch(PlayerNotExsist & e)
    {
        return FAILURE;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
{
    if(DS == NULL || GroupID == 0 || PlayerID == NULL)
    {
        return INVALID_INPUT;
    }

    try
    {
        *PlayerID = ((PlayersManager *)DS)->GetHighestLevel(GroupID);
    }
    catch(GroupNotExist & e)
    {
        return FAILURE;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
{
    if(DS == NULL || Players == NULL || numOfPlayers == NULL || GroupID == 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((PlayersManager *)DS)->GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
    }
    catch(GroupNotExist &e){
        return FAILURE;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
{
    if(DS == NULL || Players == NULL || numOfGroups < 1)
    {
        return INVALID_INPUT;
    }

    try{
        ((PlayersManager *) DS)->GetGroupsHighestLevel(numOfGroups, Players);
    }
    catch(NotEnoughGroups &e)
    {
        return FAILURE;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}

void Quit(void **DS){
    if(DS == NULL)
    {
        return;
    }

    ((PlayersManager *)*DS)->Quit((PlayersManager *)*DS);
    *DS = NULL;
}