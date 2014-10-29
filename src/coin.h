#ifndef COIN_H
#define COIN_H

#include <string>

class Coin
{
public:
    Coin();

    std::string basedir;
    std::string name;
    std::string binpath;
    std::string datadirpath;
    bool operator <(Coin &other);
    bool operator <(const Coin &other) const;
};

#endif // COIN_H

