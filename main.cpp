#include "DiscardPile.cpp"
//#include "GameCard.cpp"
#include <vector>
#include <iostream>

static const GameCardType GAME_CARD_TYPE_MARKET = {1, 1, 1, 1, 0, 5, true, "Market", "+1 Action; +1 Buy; +1 Card; +1 Coin"};
static const GameCardType GAME_CARD_TYPE_ESTATE = {0, 0, 0, 0, 1, 2, false, "Estate", "+1 Point"};
static const GameCardType GAME_CARD_TYPE_COPPER = {0, 0, 0, 1, 0, 0, false, "Copper", "+1 Coin"};
static const GameCardType GAME_CARD_TYPE_SMITHY = {0, 0, 3, 0, 0, 4, true, "Smithy", "+3 Cards"};
static const GameCardType GAME_CARD_TYPE_VILLAGE = {2, 0, 1, 0, 0, 3, true, "Village", "+2 Actions; +1 Card"};
static const GameCardType GAME_CARD_TYPE_FESTIVAL = {2, 1, 0, 2, 0, 5, true, "Festival", "+2 Actions; +1 Buy; +2 Coins"};
static const GameCardType GAME_CARD_TYPE_LABORATORY = {1, 0, 2, 0, 0, 5, true, "Laboratory", "+1 Action; +2 Cards"};


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

    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    dp.my_shuffle();
    std::cout<<"Hello\n"<<dp.getTopCard().getName();
    return 0;
}