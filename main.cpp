#include "Turn.cpp"
#include "SimpleDominionInterface.cpp"
#include <string.h>
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
            //buyDecksCounter.insert(buyDecksCounter.end(), {1,1,1,1,1,1,1,1,1,1,1});
            turn = Turn();
            simpleDominionI = SimpleDominionInterface();
            endGameStrategy = EndGameStrategy();
            turnCounter = 0;
        }
        void playGame(){
            while (!endGameStrategy.isGameOver())
            {
                turn.newTurn();
                turnCounter++;
                std::cout<<"turn:"<<turnCounter<<"\n";
                while (true)
                {
                    std::cout<<"cards in hand:\n";
                    turn.showCards(turn.hand);
                    turn.showTurnStatus();
                    std::cout<<"write 'buy', 'play', 'playall', 'discardpile' or 'end'\n";
                    char *answer = new char[30];
                    std::cin>>answer;
                    if (!strcmp(answer,"buy")){
                        std::cout<<"write id of card\n";
                        showBuyDecks();
                        std::cin>>answer;
                        char *end;
                        strtol(answer, &end, 10);
                        if (end != answer && *end == '\0'){
                            int index = std::stoi(answer)%11;
                            if (turn.buyCard(cardTypes[index], buyDecksCounter)){
                                if (answer=="2")
                                    if (endGameStrategy.decreaseProvinces()) break;
                                if (buyDecksCounter[std::stoi(answer)]==0)
                                    if (endGameStrategy.emptiedDeck()) break;
                            } else std::cout<<"couldn't perform buy action. Try again.\n";
                        } else std::cout<<"couldn't perform buy action. Try again.\n";
                    } else if (!strcmp(answer,"playall")){
                        for (int i = turn.hand.getCards().size()-1; i>=0;i--)
                            turn.playCard(i);
                    } else if (!strcmp(answer,"play")){
                        std::cout<<"write id of card\n";
                        std::cin>>answer;
                        turn.playCard(std::stoi(answer));
                    } else if (!strcmp(answer,"discardpile")){
                        std::cout<<"cards in discard pile:\n";
                        turn.showCards(turn.discardPile);
                    } else if (!strcmp(answer,"end")){
                        system("clear");
                        break;
                    }
                    if (!(turn.hand.isThereActionCard() && turn.turnStatus.actions) && !turn.turnStatus.buys)
                    {
                        system("clear");
                        std::cout<<"next moves not possible\n";
                        break;
                    }
                }

                
            }
            //std::cout<<countDeckPoints();            
            std::cout<<"Your Game is Over!\nYou've got "<<turn.getTotalPoints()<<" points and spent "<<turnCounter<<" turns of playing.\n";            
        }
};

int main(){
    Game game = Game();
    game.playGame();
    
    return 0;
}