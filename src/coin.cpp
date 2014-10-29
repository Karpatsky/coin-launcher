#include "coin.h"

Coin::Coin()
{
}
bool Coin::operator <(Coin& other)
{
    return name<other.name ? true : false;
}
bool Coin::operator <(const Coin& other) const
{
    return name<other.name ? true : false;
}

