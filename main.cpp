#include "Turn.cpp"
#include "SimpleDominionInterface.cpp"
//#include "GameCard.cpp"
#include <string>
#include <vector>
#include <iostream>
//#include "BuyDeck.cpp"

using namespace std;

#define estate GAME_CARD_TYPE_ESTATE
#define duchy GAME_CARD_TYPE_DUCHY
#define province GAME_CARD_TYPE_PROVINCE
#define copper GAME_CARD_TYPE_COPPER
#define silver GAME_CARD_TYPE_SILVER
#define gold GAME_CARD_TYPE_GOLD
#define market GAME_CARD_TYPE_MARKET
#define smithy GAME_CARD_TYPE_SMITHY
#define village GAME_CARD_TYPE_VILLAGE
#define festival GAME_CARD_TYPE_FESTIVAL
#define laboratory GAME_CARD_TYPE_LABORATORY

void printCards(std::vector<GameCard> cards){
    for (int i = 0; i < cards.size(); i++)
        std::cout<<cards[i].getName()<<",";
    std::cout<<"\n";
}


class Game {
    private:
        EndGameStrategy endGameStrategy;
        TurnStatus turnStatus;
        Turn turn;
        SimpleDominionInterface simpleDominionI;
        Hand hand;
        DiscardPile discardPile;
        Play play;
        Deck deck;
        std::vector<int> buyDecksCounter;
        std::vector<GameCardType> cardTypes;
        int turnCounter;
    public:
        Game(){
            cardTypes.emplace_back(GAME_CARD_TYPE_ESTATE);
            cardTypes.emplace_back(GAME_CARD_TYPE_DUCHY);
            cardTypes.emplace_back(GAME_CARD_TYPE_PROVINCE);
            cardTypes.emplace_back(GAME_CARD_TYPE_COPPER);
            cardTypes.emplace_back(GAME_CARD_TYPE_SILVER);
            cardTypes.emplace_back(GAME_CARD_TYPE_GOLD);
            cardTypes.emplace_back(GAME_CARD_TYPE_MARKET);
            cardTypes.emplace_back(GAME_CARD_TYPE_SMITHY);
            cardTypes.emplace_back(GAME_CARD_TYPE_VILLAGE);
            cardTypes.emplace_back(GAME_CARD_TYPE_FESTIVAL);
            cardTypes.emplace_back(GAME_CARD_TYPE_LABORATORY);
            buyDecksCounter.insert(buyDecksCounter.end(), {24, 12, 12, 60, 40, 30, 10, 10, 10, 10, 10});
            hand = Hand();
            discardPile = DiscardPile();
            play = Play();
            deck = Deck(discardPile);
            turn = Turn(hand, play, discardPile, deck, buyDecksCounter);
            simpleDominionI = SimpleDominionInterface();
            turnStatus = TurnStatus();
            endGameStrategy = EndGameStrategy();
            turnCounter = 0;
        }
        void playGame(){
            while (!endGameStrategy.isGameOver())
            {
                turn.newTurn();
                std::cout<<"turn:"<<turnCounter<<"\n";
                while (turnStatus.actions || turnStatus.buys)
                {
                    turn.showCardsInHand();
                    turn.showTurnStatus();
                    std::cout<<"to buy card, write 'buy', to play card, write 'play' where x is number of card in hand\n";
                    string answer;
                    std::cin>>answer;
                    if (answer=="buy"){
                        std::cout<<"write id of card\n";
                        // for (int i = 0; i < buyDecksCounter.size(); i++)
                        // {
                        //     std::cout<<i<<":"<<cardTypes[i].name<<" : "<<cardTypes[i].description<<". "<<buyDecksCounter[i]<<" left.\n";
                        // }
                        std::cin>>answer;
                        turn.buyCard(cardTypes[std::stoi(answer)]);
                    } else if (answer=="playall"){
                        while (turn.hand.getCards().size())
                            turn.playCard(0);
                    } else if (answer=="play"){
                        std::cout<<"write id of card\n";
                        std::cin>>answer;
                        turn.playCard(std::stoi(answer));
                    } else if (answer=="end")
                        break;
                }
                turnCounter++;
                
            }
            
        }    
};

int main(){
    // GameCard c1 = GameCard(GAME_CARD_TYPE_FESTIVAL);
    // GameCard c2 = GameCard(GAME_CARD_TYPE_COPPER);
    // GameCard c3 = GameCard(GAME_CARD_TYPE_SMITHY);
    // GameCard c4 = GameCard(GAME_CARD_TYPE_VILLAGE);
    
    // DiscardPile dp = DiscardPile();

    // EndGameStrategy endGameStrategy = EndGameStrategy();

    // BuyDeck deck0 = BuyDeck(GAME_CARD_TYPE_COPPER);

    // Deck playersDeck = Deck(dp);

    // Hand hand = Hand();
    // Play play = Play();


    // hand.draw(5, playersDeck, dp);
    Game game = Game();
    game.playGame();
    //std::cout<<"in hand";

    
    //printCards(hand.getCards());
    
    //Turn turn = Turn(hand, play, dp, playersDeck);
    
    // turn.showCardsInHand();
    // turn.showTurnStatus();
    // turn.playCard(0);

    // turn.discardPlayedCards();

    // turn.playCard(2);

    // turn.discardPlayedCards();
    // turn.drawCards(5);

    // turn.playCard(2);
    // turn.playCard(2);
    // turn.playCard(2);
    // turn.playCard(2);
    // turn.discardPlayedCards();

    // turn.drawCards(0);


    // turn.showCardsInPlay();
    // turn.showCardsInHand();
    // turn.showCardsInDiscard();
    // turn.showCardsInDeck();
    

    

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