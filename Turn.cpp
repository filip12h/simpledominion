#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <optional>
#include <iostream>
#include "EndGameStrategy.cpp"

class DiscardPile {
    private:
        std::vector<GameCard> cards;
    public:
        DiscardPile(){}
        GameCard getTopCard(){
            //if (cards.size()>0) 
            return cards[cards.size()-1];
        };
        std::vector<GameCard> getCards() {return cards;}

        void addCard(GameCard c){
            cards.emplace_back(c);
        }

        void addCards(std::vector<GameCard> c){
            cards.insert(cards.end(), c.begin(), c.end());
        }
        
        int getSize() {
            return cards.size();
        }
        
        std::vector<GameCard> my_shuffle(){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
            return cards;
        }
        void emptyDiscardPile(){
            cards.clear();
        }
};

class Deck{
    private:
        std::vector<GameCard> cardsInDeck;
        int deckSize;
        DiscardPile discardPile;
        GameCard drawOneCard(DiscardPile &dp){
            if(deckSize){
                GameCard card = cardsInDeck.back();
                cardsInDeck.pop_back();
                deckSize--;
                return card;
            } else {
                cardsInDeck = dp.my_shuffle();
                deckSize = dp.getSize();
                dp.emptyDiscardPile();
                return drawOneCard(dp);
            }
        }
    public:
        Deck(){}
        std::vector<GameCard> getCards() {return cardsInDeck;}
        Deck(DiscardPile dp){
            for (int i = 0; i < 7; i++)
            {
                cardsInDeck.emplace_back(GameCard(GAME_CARD_TYPE_COPPER));
            }
            for (int i = 0; i < 3; i++)
            {
                cardsInDeck.emplace_back(GameCard(GAME_CARD_TYPE_ESTATE));
            }
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cardsInDeck.begin(), cardsInDeck.end(), std::default_random_engine(seed));
            deckSize = 10;
            discardPile = dp;
        }
        std::vector<GameCard> draw(int n, DiscardPile &dp){
            std::vector<GameCard> cardsDrew;
            for (int i = 0; i < n; i++)
                cardsDrew.emplace_back(drawOneCard(dp));
            return cardsDrew;            
        }
};

class Play {
    private:
        std::vector<GameCard> play;
        DiscardPile discardPile;
    public:
        Play(){}
        Play(DiscardPile dp){
            discardPile = dp;
        }
        std::vector<GameCard> getCards() {return play;}
        void putIntoPlayArea(GameCard card){
            play.emplace_back(card);
        }
        std::vector<GameCard> throwAll(){
            return play;
        }
        void clearPlayArea(){
            play.clear();
        }
};

class Hand {
    private:
        std::vector<GameCard> cards;
    public:
        Hand(){}
        std::vector<GameCard> getCards() {return cards;}
        std::vector<GameCard> draw(int n, Deck &deck, DiscardPile &dp){
            std::vector<GameCard> appendCards = deck.draw(n, dp);
            cards.insert(cards.end(), appendCards.begin(), appendCards.end());
            return cards;
        }
        bool isThereActionCard(){
            for (int i = 0; i < cards.size(); i++)
                if (cards[i].isActionCard()) return true;
            return false;
        }
        GameCard play(int index){
            GameCard cardToPlay = cards[index];
            cards.erase(cards.begin()+index);
            return cardToPlay;
        }
        std::vector<GameCard> discardAll(){
            std::vector<GameCard> cardsToDiscard;
            while(cards.size())
            {
                cardsToDiscard.emplace_back(cards[0]);
                cards.erase(cards.begin());
            }
            return cardsToDiscard;
        }
};

class Turn {
    private:
        template<typename T>
        int countPoints(T t){
            int counter = 0;
            std::vector<GameCard> cards = t.getCards();
            for (int i = 0; i < cards.size(); i++){
                counter += cards[i].getPoints();
            }
            return counter;
        }
    public:
        TurnStatus turnStatus;
        Hand hand;
        Play play;
        DiscardPile discardPile;
        Deck deck;
        Turn(){
            turnStatus.actions = 1;
            turnStatus.buys = 1;
            turnStatus.coins = 0;
            hand = Hand();
            play = Play();
            discardPile = DiscardPile();
            deck = Deck(discardPile);
        }
        int getTotalPoints(){
            return countPoints(hand)+countPoints(play)+countPoints(discardPile)+countPoints(deck);
        }
        void showTurnStatus(){
            std::cout<<"actions:"<<turnStatus.actions<<"\nbuys:"<<turnStatus.buys<<"\ncoins:"<<turnStatus.coins<<"\n";
        }
        void showCardsInHand(){
            std::cout<<"in hand\n";
            for (int i = 0; i < hand.getCards().size(); i++)
                std::cout<<i<<": "<<hand.getCards()[i].getName()<<"\n";
        }
        void showCardsInDiscard(){
            std::cout<<"in discard\n";
            for (int i = 0; i < discardPile.getCards().size(); i++)
                std::cout<<i<<": "<<discardPile.getCards()[i].getName()<<"\n";
        }
        void showCardsInPlay(){
            std::cout<<"in play\n";
            for (int i = 0; i < play.getCards().size(); i++)
                std::cout<<i<<": "<<play.getCards()[i].getName()<<"\n";
        }
        // void showCardsInDeck(){
        //     std::cout<<"in deck\n";
        //     for (int i = 0; i < deck.getCards().size(); i++)
        //         std::cout<<i<<": "<<deck.getCards()[i].getName()<<"\n";
        // }
        void drawCards(int n){
            hand.draw(n, deck, discardPile);
        }
        void newTurn(){
            while (hand.getCards().size())
                discardPile.addCards(hand.discardAll());
            turnStatus.actions = 1;
            turnStatus.buys = 1;
            turnStatus.coins = 0;
            discardPlayedCards();
            drawCards(5);
        }
        void discardPlayedCards(){
            std::vector<GameCard> playedCards = play.throwAll();
            discardPile.addCards(playedCards);
            play.clearPlayArea();
        }
        GameCard playCard(int index){
            GameCard playedCard = hand.play(index);
            if (playedCard.isActionCard() && turnStatus.actions == 0){ 
                std::cout<<"no more actions left\n";
            } else {
                std::cout<<"played card:"<<playedCard.getName()<<"\n";
                if (playedCard.isActionCard())
                    turnStatus.actions--;
                hand.draw(playedCard.evaluate(turnStatus), deck, discardPile);
                play.putIntoPlayArea(playedCard);
                // showCardsInHand();
                // showTurnStatus();
            }
            return playedCard;
        }
        bool buyCard(GameCardType cardType, std::vector<int> &buyDecksCounter){
            if (turnStatus.coins>= cardType.cost && buyDecksCounter[cardType.id]>0){
                turnStatus.coins -= cardType.cost;
                turnStatus.buys--;
                discardPile.addCard(GameCard(cardType));
                buyDecksCounter[cardType.id]--;
                return true;
            }
            return false;
        }
};