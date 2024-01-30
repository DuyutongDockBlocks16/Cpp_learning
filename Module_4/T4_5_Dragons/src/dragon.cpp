#include "dragon.hpp"

std::string Dragon::GetName() const {
    return name_;
}

size_t Dragon::GetAge() const {
    return age_;
}

size_t Dragon::GetSize() const {
    return size_;
}

std::vector<Treasure> Dragon::GetTreasures() const {
    return treasures_;
}

std::ostream& operator<<(std::ostream& os, const Dragon& dragon)
{
    os << "Dragon named: " << dragon.GetName() << ", age: " << dragon.GetAge() << ", size: " << dragon.GetSize() << "\n";
    os << "Treasures:\n";

    for (const Treasure& treasure : dragon.GetTreasures())
    {
        os << treasure.name << "\n";
    }

    return os;
}
