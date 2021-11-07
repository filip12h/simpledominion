#include <string>
#include <utility>
#include "TurnStatus.cpp"

//static const GameCardType GAME_CARD_TYPE_MARKET = GameCardType(1, 1, 1, 1, 0, 5, true, "Market", "+1 Action; +1 Buy; +1 Card; +1 Coin");
//static const GameCardType GAME_CARD_TYPE_ESTATE = GameCardType(0, 0, 0, 0, 1, 2, false, "Estate", "+1 Point");
//static const GameCardType GAME_CARD_TYPE_COPPER = GameCardType(0, 0, 0, 1, 0, 0, false, "Copper", "+1 Coin");
//static const GameCardType GAME_CARD_TYPE_SMITHY = GameCardType(0, 0, 3, 0, 0, 4, true, "Smithy", "+3 Cards");
//static const GameCardType GAME_CARD_TYPE_VILLAGE = GameCardType(2, 0, 1, 0, 0, 3, true, "Village", "+2 Actions; +1 Card");
//static const GameCardType GAME_CARD_TYPE_FESTIVAL = GameCardType(2, 1, 0, 2, 0, 5, true, "Festival", "+2 Actions; +1 Buy; +2 Coins");
//static const GameCardType GAME_CARD_TYPE_LABORATORY = GameCardType(1, 0, 2, 0, 0, 5, true, "Laboratory", "+1 Action; +2 Cards");

struct GameCardType {
    int plusActions, plusBuys, plusCards, plusCoins, points, cost;
    bool isAction;
    std::string name, description;
};

class CardInterface {
    public:
        virtual int evaluate(TurnStatus& ts) = 0;
        GameCardType getCardType() {return cardType;}
    private:
        GameCardType cardType;
};

class GameCard:CardInterface {
    protected:
        int plusActions, plusBuys, plusCards, plusCoins, points, cost;
        bool isAction;
        std::string name, description;
    public:
        GameCard(GameCardType cardType){
            plusActions =   cardType.plusActions;
            plusBuys =      cardType.plusBuys;
            plusCards =     cardType.plusCards;
            plusCoins =     cardType.plusCoins;
            points =        cardType.points;
            cost =          cardType.cost;
            isAction =      cardType.isAction;
            name =          cardType.name;
            description =   cardType.description;
        }
        int getPlusActions() {return plusActions;}
        int getPlusBuys() {return plusBuys;}
        int getPlusCards() {return plusCards;}
        int getPlusCoins() {return plusCoins;}
        int getPoints() {return points;}
        bool isActionCard() {return isAction;}
        std::string getName() {return name;}
        std::string getDescription() {return description;}
        int evaluate(TurnStatus &ts){
            ts.actions += getPlusActions();
            ts.buys += getPlusBuys();
            ts.coins += getPlusCoins();
            return getPlusCards();
        }
        //I decided to not include getCardType since it is obvious from getName()
};