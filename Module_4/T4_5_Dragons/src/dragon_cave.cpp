#include "dragon_cave.hpp"

// Define DragonCave's methods here

// DragonCave 类的构造函数
DragonCave::DragonCave()
{
    // 默认构造函数，无需额外的初始化
}

// DragonCave 类的析构函数
DragonCave::~DragonCave()
{
    // 删除 DragonCave 中的所有龙
    for (Dragon* dragon : dragons_)
    {
        delete dragon;
    }
}

// 获取 DragonCave 中的龙的列表
const std::list<Dragon*>& DragonCave::GetDragons() const
{
    return dragons_;
}

// 添加龙到 DragonCave 中
void DragonCave::Accommodate(Dragon* dragon)
{
    if (dragon)
    {
        dragons_.push_back(dragon);
    }
}

// 根据龙的名称从 DragonCave 中移除龙
void DragonCave::Evict(const std::string& dragonName)
{
    for (auto it = dragons_.begin(); it != dragons_.end(); ++it)
    {
        if ((*it)->GetName() == dragonName)
        {
            it = dragons_.erase(it);
            return; // 找到并删除一个匹配的龙后，结束函数
        }
    }
}

// 重载 << 操作符，用于打印 DragonCave 中的龙列表
std::ostream& operator<<(std::ostream& os, const DragonCave& cave)
{
    os << "DragonCave dwellers:\n\n";
    for (const Dragon* dragon : cave.dragons_)
    {
        os << *dragon << "\n";
    }
    return os;
}