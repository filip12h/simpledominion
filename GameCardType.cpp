#include <string>

static const GameCardType GAME_CARD_TYPE_MARKET = GameCardType(1, 1, 1, 1, 0, 5, true, "Market", "+1 Action; +1 Buy; +1 Card; +1 Coin");
static const GameCardType GAME_CARD_TYPE_ESTATE = GameCardType(0, 0, 0, 0, 1, 2, false, "Estate", "+1 Point");
static const GameCardType GAME_CARD_TYPE_COPPER = GameCardType(0, 0, 0, 1, 0, 0, false, "Copper", "+1 Coin");
static const GameCardType GAME_CARD_TYPE_SMITHY = GameCardType(0, 0, 3, 0, 0, 4, true, "Smithy", "+3 Cards");
static const GameCardType GAME_CARD_TYPE_VILLAGE = GameCardType(2, 0, 1, 0, 0, 3, true, "Village", "+2 Actions; +1 Card");
static const GameCardType GAME_CARD_TYPE_FESTIVAL = GameCardType(2, 1, 0, 2, 0, 5, true, "Festival", "+2 Actions; +1 Buy; +2 Coins");
static const GameCardType GAME_CARD_TYPE_LABORATORY = GameCardType(1, 0, 2, 0, 0, 5, true, "Laboratory", "+1 Action; +2 Cards");

class GameCardType {
    protected:
        int plusActions, plusBuys, plusCards, plusCoins, points, cost;
        bool isAction;
        std::string name, description;
    public:
        GameCardType(int pa, int pb, int pca, int pco, int p, int c, bool isA, std::string n, std::string d){
            plusActions = pa;
            plusBuys = pb;
            plusCards = pca;
            plusCoins = pco;
            points = p;
            cost = c;
            isAction = isA;
            name = n;
            description = d;
        }
        int getPlusActions() {return plusActions;}
        int getPlusBuys() {return plusBuys;}
        int getPlusCards() {return plusCards;}
        int getPlusCoins() {return plusCoins;}
        int getPoints() {return points;}
        int isAction() {return isAction;}
        std::string getName() {return name;}
        std::string getDescription() {return description;}
};