#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Card {
private:
    char suits;
    char ranks;

public:
    Card(){
    };
    Card(char r, char s)
{
  ranks = r;
  suits = s;
}
    void display();
    int compare(const Card&);
};

class Deck
{
    private:
        Card pack[52]; 
        int cardTotal;
    public:
        Deck();
        void display();
        void shuffle();
        Card deal();
        bool isEmpty();
};


int Card::compare(const Card& other)
{
  int thisValue, otherValue;

    if (this->ranks >= '2' && this->ranks <= '9'){
      thisValue = this->ranks - '0';
    }
    else if (this->ranks == 'T'){
      thisValue = 10;
    }
    else if (this->ranks == 'J'){
      thisValue = 11;
    }
    else if (this->ranks == 'Q'){
      thisValue = 12;
    }
    else if (this->ranks == 'K'){
      thisValue = 13;
    }
    else{
      thisValue = 0;
    }

    if (other.ranks >= '2' && other.ranks <= '9'){
      otherValue = other.ranks - '0';
    }
    else if (other.ranks == 'T'){
      otherValue = 10;
    }
    else if (other.ranks == 'J'){
      otherValue = 11;
    }
    else if (other.ranks == 'Q'){
      otherValue = 12;
    }
    else if (other.ranks == 'K'){
      otherValue = 13;
    }
    else{
      otherValue = 0;
    }
  
    if (thisValue > otherValue){
        return 1;
    }
    else if (thisValue < otherValue){
        return 0;
    }
    else{
        return -1;
    }
}

void Card::display()
{
    if (ranks == 'T'){
      cout << "10" << suits << " ";
    }
    else if (ranks == '1'){
      cout << "A" << suits << " ";
    }
    else if (ranks == 'J'){
      cout << "J" << suits << " ";
    }
    else if (ranks == 'Q'){
      cout << "Q" << suits << " ";
    }
    else if (ranks == 'K'){
      cout << "K" << suits << " ";
    }
    else{
     cout << ranks << suits << " ";
    }
}

Deck::Deck() : cardTotal(52){
    char ranks[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9','T', 'J', 'Q', 'K'};
    char suits[] = {'H', 'D', 'S', 'C'};
    
    int i = 0;
    for (char rank : ranks) {
        for (char suit: suits){
            pack[i] = Card(rank, suit);
            i += 1;
        }
    }
}

Card Deck::deal() {
     int c = cardTotal - 1;
     if (isEmpty()){
        throw runtime_error("Deck is empty");
     }
   
   Card dealtCard = pack[c];
   cardTotal = c;
   return dealtCard;
}

void Deck::display() {
    for (int i = 0; i < cardTotal; ++i) {
        pack[i].display();
        if (i != cardTotal - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

void Deck::shuffle() {
    srand(time(0));

    for (int i = 0; i < cardTotal; i++) {
        int j = rand() % cardTotal;
        swap(pack[i], pack[j]);
    }
}

bool Deck::isEmpty() {
  return cardTotal == 0;
}

int main() {
    string p1, p2;
    int games;

    cout << "Enter the name of the first player: ";
    cin >> p1;
    cout << "Enter the name of the second player: ";
    cin >> p2;

    cout << "How many games will they play? ";
    cin >> games;

    Deck myDeck;
    cout << endl;
    cout << "Original Deck: " << endl;
    myDeck.display();
    cout << endl;

    cout << "Shuffled Deck: " << endl;
    myDeck.shuffle();
    myDeck.display();
    cout << endl;
  
    int p1_wins = 0;
    int round_count = 1;
    int p2_wins = 0;
    int tie = 0;
    try {
    for (int i = 0; i < games; i++) {
      Card c1 = myDeck.deal();
      Card c2 = myDeck.deal();
      cout << "Game " << round_count << endl;
      cout << "--------" << endl;
      myDeck.shuffle();
      cout << "            " <<  p1 << "=>" ;
      c1.display(); 
      cout << "            " ;
      cout << "            "  << p2 << "=>";
      c2.display(); 
      cout << "            " ;
      int result = c1.compare(c2);
      if (result == 1) {
          cout << p1 << " => Winner" << endl;
          p1_wins += 1;
      } else if (result == 0) {
         cout << p2 << " => Winner" << endl;
         p2_wins += 1;
      } else {
         cout << "Tie game" << endl;
         tie += 1;
      }
      cout << endl;
      round_count += 1;
    }
} catch(const runtime_error& error){
  cout << "Error - " << error.what() << endl;
  cout << endl;
}
    cout << "------Final Stats-------" << endl;
    cout << "               " << p1 << " vs. " << p2 << endl;
    cout << "Wins " << "            " << p1_wins << "        " << p2_wins << endl;
    cout << "Losses " << "          " << p2_wins << "        " << p1_wins << endl;
    cout << "Ties " << "            " << tie << "        " << tie << endl;
    }

