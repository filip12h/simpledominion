#include "Turn.cpp"
#include "SimpleDominionInterface.cpp"
#include <string>
#include <vector>
#include <iostream>

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
        Turn turn;
        SimpleDominionInterface simpleDominionI;
        Hand hand;
        DiscardPile discardPile;
        Play play;
        Deck deck;
        std::vector<int> buyDecksCounter;
        std::vector<GameCardType> cardTypes;
        int turnCounter;
        void showBuyDecks(){
            for (int i = 0; i < buyDecksCounter.size(); i++)
            {
                if (turn.turnStatus.coins >= cardTypes[i].cost){
                    std::cout<<"id:"<<i<<", "<<cardTypes[i].name<<": "<<cardTypes[i].description<<". Cost:"<<cardTypes[i].cost<<". Reamins in deck: "<<buyDecksCounter[i]<<"\n";
                }
            }
            
        };
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
            turn = Turn(hand, play, discardPile, deck);
            simpleDominionI = SimpleDominionInterface();
            endGameStrategy = EndGameStrategy();
            turnCounter = 0;
        }
        void playGame(){
            while (!endGameStrategy.isGameOver())
            {
                //system("clear");
                turn.newTurn();
                std::cout<<"turn:"<<turnCounter<<"\n";
                while (true)
                {
                    turn.showCardsInHand();
                    turn.showTurnStatus();
                    std::cout<<"write 'buy', 'play', 'playall' or 'end'\n";
                    string answer;
                    std::cin>>answer;
                    if (answer=="buy"){
                        std::cout<<"write id of card\n";
                        showBuyDecks();
                        std::cin>>answer;
                        turn.buyCard(cardTypes[std::stoi(answer)], buyDecksCounter);
                    } else if (answer=="playall"){
                        while (turn.hand.getCards().size())
                            turn.playCard(0);
                    } else if (answer=="play"){
                        std::cout<<"write id of card\n";
                        std::cin>>answer;
                        turn.playCard(std::stoi(answer));
                    } else if (answer=="end")
                        break;
                    if (!(turn.hand.isThereActionCard() && turn.turnStatus.actions) && !turn.turnStatus.buys)
                    {
                        std::cout<<"next moves not possible\n";
                        break;
                    }
                }

                turnCounter++;
                
            }
            
        }    
};

int main(){
    Game game = Game();
    game.playGame();
    
    return 0;
}