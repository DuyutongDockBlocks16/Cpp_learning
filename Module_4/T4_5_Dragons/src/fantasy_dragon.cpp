#include "fantasy_dragon.hpp"

// Define FantasyDragon's methods here


void FantasyDragon::Eat(std::list<Food> &foodList) {
    for (auto it = foodList.begin(); it != foodList.end();)
    {
        if (it->type == People || it->type == PeopleFood)
        {
            // 吃食物，增加大小
            size_++;
            // 打印被吃掉的食物信息
            std::cout << "Fantasy dragon ate: " << it->name << "\n";
            // 从食物列表中移除被吃掉的食物
            it = foodList.erase(it);
        }
        else
        {
            // 不吃这种食物，继续检查下一个食物
            ++it;
        }
    }
}

void FantasyDragon::Hoard(std::list<Treasure> &treasureList) {
    for (auto it = treasureList.begin(); it != treasureList.end();)
    {
        if (it->type == Jewellery)
        {
            // hoard 宝藏，添加到宝藏列表
            treasures_.push_back(*it);
            // 打印 hoard 的宝藏信息
            std::cout << "Fantasy dragon hoarded: " << it->name << "\n";
            // 从传入的宝藏列表中移除 hoard 的宝藏
            it = treasureList.erase(it);
        }
        else
        {
            // 不 hoard 这种宝藏，继续检查下一个宝藏
            ++it;
        }
    }
}
