#ifndef BILET_NORMAL_H
#define BILET_NORMAL_H

#include "Bilet_Template.h"

class Bilet_Normal : public Bilet_Template<int> {
public:
    Bilet_Normal(int rand, int coloana);
    Bilet_Normal();
    ~Bilet_Normal() override = default;

    [[nodiscard]] std::string getType() const override;
};

#endif // BILET_NORMAL_H