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
        GameCard drawOneCard(){
            if(deckSize){
                GameCard card = cardsInDeck.back();
                cardsInDeck.pop_back();
                deckSize--;
                return card;
            } else {
                cardsInDeck = discardPile.my_shuffle();
                deckSize = discardPile.getSize();
                discardPile.emptyDiscardPile();
                return drawOneCard();
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
        std::vector<GameCard> draw(int n){
            std::vector<GameCard> cardsDrew;
            for (int i = 0; i < n; i++)
                cardsDrew.emplace_back(drawOneCard());
            return cardsDrew;            
        }
};

class Play {
    private:
        std::vector<GameCard> cardsInPlay;
        DiscardPile discardPile;
    public:
        Play(){}
        Play(DiscardPile dp){
            discardPile = dp;
        }
        std::vector<GameCard> getCards() {return cardsInPlay;}
        void putIntoPlayArea(GameCard card){
            cardsInPlay.emplace_back(card);
        }
        std::vector<GameCard> throwAll(){
            /*for (int i = 0; i < cardsInPlay.size(); i++)
            {
                discardPile.addCard(cardsInPlay[i]);
            }*/
            return cardsInPlay;
        }
        void clearPlayArea(){
            cardsInPlay.clear();
        }
};

class Hand {
    private:
        std::vector<GameCard> cards;
    public:
        Hand(){}
        std::vector<GameCard> getCards() {return cards;}
        std::vector<GameCard> draw(int n, Deck &deck){
            std::vector<GameCard> appendCards = deck.draw(n);
            cards.insert(cards.end(), appendCards.begin(), appendCards.end());
            return cards;
        }
        bool isActionCard(int index){
            return cards[index].isActionCard();
        }
        GameCard play(int index){
            GameCard cardToPlay = cards[index];
            cards.erase(cards.begin()+index);
            return cardToPlay;
        }
};

class Turn {
    private:
        TurnStatus turnStatus;
        Hand cardsInHand;
        Play cardsInPlay;
        DiscardPile discardPile;
        Deck deck;
    public:
        Turn(Hand h, Play p, DiscardPile dp, Deck d){
            turnStatus.actions = 1;
            turnStatus.buys = 1;
            turnStatus.coins = 0;
            cardsInHand = h;
            cardsInPlay = p;
            discardPile = dp;
            deck = d;
        }
        GameCard playCard(int index){
            GameCard playedCard = cardsInHand.play(index);
            if (cardsInHand.isActionCard(index) && turnStatus.actions == 0){ 
                std::cout<<"no more actions left";
            } else {
                if (turnStatus.actions>0)
                    turnStatus.actions--;
                cardsInHand.draw(playedCard.evaluate(turnStatus), deck);
            }
            return playedCard;
        }
};