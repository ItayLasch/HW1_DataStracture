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
#endif