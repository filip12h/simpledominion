#include "Hand.cpp"
//#include "GameCard.cpp"
#include <vector>
#include <iostream>
//#include "BuyDeck.cpp"

void printCards(std::vector<GameCard> cards){
    for (int i = 0; i < cards.size(); i++)
        std::cout<<cards[i].getName()<<",";
    std::cout<<"\n";
}

int main(){
    GameCard c1 = GameCard(GAME_CARD_TYPE_FESTIVAL);
    GameCard c2 = GameCard(GAME_CARD_TYPE_COPPER);
    GameCard c3 = GameCard(GAME_CARD_TYPE_SMITHY);
    GameCard c4 = GameCard(GAME_CARD_TYPE_VILLAGE);
    
    DiscardPile dp = DiscardPile();
    dp.addCard(c1);
    dp.addCard(c2);
    dp.addCard(c3);
    dp.addCard(c4);

    EndGameStrategy endGameStrategy = EndGameStrategy();

    BuyDeck deck0 = BuyDeck(GAME_CARD_TYPE_COPPER);

    Deck playersDeck = Deck(dp);

    Hand cardsInHand = Hand();
    Play play = Play();
    Turn turn = Turn(cardsInHand, play, dp, playersDeck);

    cardsInHand.draw(5, playersDeck);
    std::cout<<"in hand";
    printCards(cardsInHand.getCards());
    std::cout<<"players deck";
    printCards(playersDeck.getCards());

    cardsInHand.draw(5, playersDeck);
    std::cout<<"in hand";
    printCards(cardsInHand.getCards());

    std::cout<<"players deck";
    printCards(playersDeck.getCards());
    //printCards(dp.getCards());
    cardsInHand.draw(4, playersDeck);
    std::cout<<"players deck";
    printCards(playersDeck.getCards());
    std::cout<<"in hand";
    printCards(cardsInHand.getCards());

/*
    std::vector<GameCard> hand =  playersDeck.draw(5);
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout<<hand[i].getName()<<",";
    }
    std::cout<<",";

    hand =  playersDeck.draw(9);
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout<<hand[i].getName()<<",";
    }

    std::cout<<deck0.deckSize()<<"\n";
    deck0.buy();
    std::cout<<deck0.deckSize()<<"\n";

    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();*/
    return 0;
}