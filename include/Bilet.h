#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>

class Bilet
{
public:
    virtual ~Bilet() = default;

    [[nodiscard]] virtual std::string
    getType() const = 0;
};

#endif