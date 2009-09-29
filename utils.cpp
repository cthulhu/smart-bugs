#include "utils.h"
bool Position::operator==(Position b)
{
    return this->x == b.x && this->y == b.y;
}