#include "DiscardPile.cpp"
//#include "GameCard.cpp"
#include <vector>
#include <iostream>
//#include "BuyDeck.cpp"

int main(){
    std::vector<GameCard> cards;
    GameCard c1 = GameCard(GAME_CARD_TYPE_FESTIVAL);
    GameCard c2 = GameCard(GAME_CARD_TYPE_COPPER);
    GameCard c3 = GameCard(GAME_CARD_TYPE_SMITHY);
    GameCard c4 = GameCard(GAME_CARD_TYPE_VILLAGE);
    
    cards.emplace_back(c1);
    cards.emplace_back(c2);
    DiscardPile dp = DiscardPile();
    dp.addCard(c1);
    dp.addCard(c2);
    dp.addCard(c3);
    dp.addCard(c4);

    EndGameStrategy endGameStrategy = EndGameStrategy();

    BuyDeck deck0 = BuyDeck(GAME_CARD_TYPE_COPPER);

    Deck playersDeck = Deck(dp);

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
    /*
    std::cout<<",";
    hand =  playersDeck.draw(6);
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout<<hand[i].getName()<<",";
    }
    std::cout<<",";
    hand =  playersDeck.draw(6);
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout<<hand[i].getName()<<",";
    }
    std::cout<<",";
*/
    

    std::cout<<deck0.deckSize()<<"\n";
    deck0.buy();
    std::cout<<deck0.deckSize()<<"\n";

    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    return 0;
}