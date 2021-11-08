#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <optional>
#include "EndGameStrategy.cpp"

class DiscardPile {
    private:
        std::vector<GameCard> cards;
    public:
        DiscardPile(){}
        GameCard getTopCard(){
            //if (cards.size()>0) 
            return cards[cards.size()-1];
        };
        void addCard(GameCard c){
            cards.emplace_back(c);
        }
        
        int getSize() {
            return cards.size();
        }
        
        std::vector<GameCard> my_shuffle(){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
            return cards;
        }
};