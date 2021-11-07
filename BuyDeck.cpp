#include "GameCard.cpp"

class BuyDeck {
    private:
        int cardCount;
        GameCardType cardType;
    public:
        BuyDeck(GameCardType _cardType){
            cardCount = 10;
            cardType = _cardType;
        }
        GameCardType buy(){
            cardCount--;
            return cardType;
        }
        int deckSize(){
            return cardCount;
        }
};