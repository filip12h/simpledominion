#include <string>
#include <vector>

class Card {
    public:
        std::string name, description;
        int cost;
};

class GameState {
    public:
        std::vector<Card> handCards;
        std::vector<std::pair<int, Card>> buyCards;
        Card discardPileTop;
        int deckSize, discardPileSize, points, turn;
};

class SimpleDominionInterface {
    public:
        GameState playCard(int handIdx);
        GameState endPlayCardPhase();
        GameState buyCard(int buyCardIdx);
        GameState endTurn();
};