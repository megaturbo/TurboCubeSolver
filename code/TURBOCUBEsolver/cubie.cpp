#include "cubie.h"

//Public methods
//Constructor
Cubie::Cubie(color* c)
{
    for(int i = 0; i<3; i++){
        colors.append(c[i]);
    }
    this->id = colors[0] + colors[1] * 6 + colors[2] *  36;
}

//Utility methods

bool Cubie::operator==(const Cubie c) const {
    return (this->id==c.id);
}

bool Cubie::operator<(const Cubie c) const {
    return (this->id<c.id);
}

//Private methods
