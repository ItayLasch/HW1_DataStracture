#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class EmptyDataSystem : public std::exception
{
};
class NullArg : public std::exception
{
};
class PlayerNotExsist : public std::exception
{
};

class PlayerExist : public std::exception
{
};

class GroupNotExist : public std::exception
{
};

class GroupExist : public std::exception
{
};

class NotEnoughGroups : public std::exception
{
};
#endif