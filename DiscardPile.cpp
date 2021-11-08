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
        void emptyDiscardPile(){
            cards.clear();
        }
};

class Deck{
    private:
        std::vector<GameCard> cardsInDeck;
        int deckSize;
        DiscardPile discardPile;
        GameCard drawOneCard(){
            if(deckSize){
                GameCard card = cardsInDeck.back();
                cardsInDeck.pop_back();
                deckSize--;
                return card;
            } else {
                cardsInDeck = discardPile.my_shuffle();
                deckSize = discardPile.getSize();
                discardPile.emptyDiscardPile();
                return drawOneCard();
            }
        }
    public:
        Deck(DiscardPile dp){
            for (int i = 0; i < 7; i++)
            {
                cardsInDeck.emplace_back(GameCard(GAME_CARD_TYPE_COPPER));
            }
            for (int i = 0; i < 3; i++)
            {
                cardsInDeck.emplace_back(GameCard(GAME_CARD_TYPE_ESTATE));
            }
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cardsInDeck.begin(), cardsInDeck.end(), std::default_random_engine(seed));
            deckSize = 10;
            discardPile = dp;
        }
        std::vector<GameCard> draw(int n){
            std::vector<GameCard> cardsDrew;
            for (int i = 0; i < n; i++)
                cardsDrew.emplace_back(drawOneCard());
            return cardsDrew;            
        }
};