#include "troll.hpp"


std::ostream& operator<<(std::ostream& os, const Troll& troll) {
    os << "Troll " << troll.getName() << " with " << troll.getHitPoints() << " HP";
    return os;
}