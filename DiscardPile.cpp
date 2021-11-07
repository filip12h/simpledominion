#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <optional>
#include "GameCard.cpp"

class DiscardPile {
    private:
        std::vector<GameCard> cards;
    public:
        DiscardPile(){}
        //std::optional<CardInterface*> getTopCard(){if (cards.size()>0) return &cards[cards.size()-1]; return std::nullopt;};
        /*void addCards(std::vector<CardInterface> _cards){
            using std::begin; using std::end;
            cards.insert(std::end(cards), std::begin(_cards), std::end(_cards));
        }*/
        
        int getSize() {
            return cards.size();
        }
        /*
        std::vector<CardInterface> my_shuffle(){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
            return cards;
        }*/
};