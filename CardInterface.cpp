#include <utility>
#include "GameCardType.cpp"
#include "TurnStatus.cpp"

class CardInterface {
    public:
        virtual std::pair<int, int> evaluate(TurnStatus& ts) = 0;
        GameCardType getCardType() {return cardType;}
    protected:
        GameCardType cardType;
        
};
