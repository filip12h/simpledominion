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
        int increaseNumOfEmptyDecks(int n){
            numOfEmptyDecks++;
            return numOfEmptyDecks;
        }
        int getNumOfEmptyDecks(int n){
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
        int decreaseNumOfProvinces(int n){
            counter--;
            return n;
        }
        int getNumOfProvinces(int n){
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
        bool isGameOver(){
            return atLeastNEmptyDecks.checkCriteria() || noProvincesLeft.checkCriteria();
        }
};