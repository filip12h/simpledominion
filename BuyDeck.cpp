#include "GameCard.cpp"
#include <optional>

class BuyDeck {
    private:
        int cardCount;
        GameCardType cardType;
    public:
        BuyDeck(GameCardType _cardType){
            cardCount = 10;
            cardType = _cardType;
        }
        GameCard buy(){
            GameCard card = GameCard(cardType);
            cardCount--;
            return card;
        }
        int deckSize(){
            return cardCount;
        }
};