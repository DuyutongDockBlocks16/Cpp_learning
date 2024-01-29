#include "dragon.hpp"

std::ostream& operator<<(std::ostream& os, const Dragon& dragon) {
    os << "Troll " << dragon.getName() << " with " << dragon.getHitPoints() << " HP";
    return os;
}
