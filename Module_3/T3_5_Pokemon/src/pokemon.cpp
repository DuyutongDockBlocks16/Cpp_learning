#include "pokemon.hpp"
#include <list>
#include <algorithm>

PokemonCollection::PokemonCollection(PokemonCollection collection, PokemonCollection collection2) {

    pokemons_.merge(collection.pokemons_);
    pokemons_.merge(collection2.pokemons_);

    pokemons_.sort();
    pokemons_.unique([](const auto& lhs, const auto& rhs){
        return lhs.first == rhs.first && lhs.second == rhs.second;
    });

}

void PokemonCollection::Add(const std::string &name, size_t id) {

    std::pair<std::string, size_t> newPokemon(name, id);
    pokemons_.push_back(newPokemon);

}

bool PokemonCollection::Remove(const std::string &name, size_t id) {

    for (auto it = pokemons_.begin(); it != pokemons_.end(); ++it) {
        if (it->first == name && it->second == id) {
            pokemons_.erase(it);
            return true;
        }
    }
    return false;
}

void PokemonCollection::Print() const {
//    for (const auto& pokemon : pokemons_) {
//        std::cout << "id: " << pokemon.second << ", name: " << pokemon.first << "\n";
//    }

    std::cout << "111111111111111111111111";
}

void PokemonCollection::SortByName() {
    pokemons_.sort([](const auto& lhs, const auto& rhs) {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    });
}

void PokemonCollection::SortById() {
    pokemons_.sort([](const auto& lhs, const auto& rhs) {
        if (lhs.second != rhs.second) {
            return lhs.second < rhs.second;
        }
        return lhs.first < rhs.first;
    });

}
