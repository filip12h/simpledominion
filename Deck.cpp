#include <vector>
#include "DiscardPile.cpp"


class Deck{
    private:
        std::vector<GameCard> cardsInDeck;
        int deckSize;
        DiscardPile discardPile;
    public:
        Deck(){
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
            discardPile = DiscardPile();
        }
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
        std::vector<GameCard> draw(int n){
            std::vector<GameCard> cardsDrew;
            for (int i = 0; i < n; i++)
                cardsDrew.emplace_back(drawOneCard());
            return cardsDrew;            
        }
};