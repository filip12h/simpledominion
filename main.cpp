#include "Turn.cpp"
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

    EndGameStrategy endGameStrategy = EndGameStrategy();

    BuyDeck deck0 = BuyDeck(GAME_CARD_TYPE_COPPER);

    Deck playersDeck = Deck(dp);

    Hand hand = Hand();
    Play play = Play();


    hand.draw(5, playersDeck, dp);
    //std::cout<<"in hand";

    
    //printCards(hand.getCards());
    
    Turn turn = Turn(hand, play, dp, playersDeck);
    
    turn.showCardsInHand();
    turn.showTurnStatus();
    turn.playCard(0);

    turn.discardPlayedCards();

    turn.playCard(2);

    turn.discardPlayedCards();
    turn.drawCards(5);

    turn.playCard(2);
    turn.playCard(2);
    turn.playCard(2);
    turn.playCard(2);
    turn.discardPlayedCards();

    turn.drawCards(0);


    turn.showCardsInPlay();
    turn.showCardsInHand();
    turn.showCardsInDiscard();
    turn.showCardsInDeck();
    

    

    /*std::cout<<"players deck";
    printCards(playersDeck.getCards());

    hand.draw(5, playersDeck);
    std::cout<<"in hand";
    printCards(hand.getCards());

    std::cout<<"players deck";
    printCards(playersDeck.getCards());

    hand.draw(4, playersDeck);
    std::cout<<"players deck";
    printCards(playersDeck.getCards());
    std::cout<<"in hand";
    printCards(hand.getCards());*/

    return 0;
}