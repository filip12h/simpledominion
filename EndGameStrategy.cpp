#include <vector>
#include "BuyDeck.cpp"

class AtLeastNEmptyDecks{
    private:
        int emptyDecksLimit;
        int numOfEmptyDecks = 0;
    public:
        AtLeastNEmptyDecks(){}
        AtLeastNEmptyDecks(int n){
            emptyDecksLimit = n;
        }
        bool checkCriteria(){
            if (numOfEmptyDecks>=emptyDecksLimit) return true;
            return false;
        }
        bool increaseNumOfEmptyDecks(){
            numOfEmptyDecks++;
            return checkCriteria();
        }
        int getNumOfEmptyDecks(){
            return numOfEmptyDecks;
        }
};

class NoProvincesLeft{
    private:
        int counter;
    public:
        NoProvincesLeft(){}
        NoProvincesLeft(int n){
            counter = n;
        }
        bool checkCriteria(){
            if (counter==0)
                return true;
            return false;
        }
        void decreaseNumOfProvinces(){
            counter--;
        }
        int getNumOfProvinces(){
            return counter;
        }
};

class EndGameStrategy {
    private:
        NoProvincesLeft noProvincesLeft;
        AtLeastNEmptyDecks atLeastNEmptyDecks;
    public:
        EndGameStrategy(){
            atLeastNEmptyDecks = AtLeastNEmptyDecks(3);
            noProvincesLeft = NoProvincesLeft(12);
        }
        bool emptiedDeck(){
            atLeastNEmptyDecks.increaseNumOfEmptyDecks();
            return atLeastNEmptyDecks.checkCriteria();
        }
        bool decreaseProvinces(){
            noProvincesLeft.decreaseNumOfProvinces();
            return noProvincesLeft.checkCriteria();
        }
        bool isGameOver(){
            return atLeastNEmptyDecks.checkCriteria() || noProvincesLeft.checkCriteria();
        }
};