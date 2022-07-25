
#ifndef DECK_H
#define DECK_H
#include <iostream>
#include "user.h"

const int ROW = 5;
const int COL = 5;
using namespace std;
//this class plays game, handles flow of game. 
class Table
{

	private:
		int number;
		string suit;
	
	public:
		Table();
		Table(int num, string suit);
		friend ostream& operator <<(ostream& couts ,const Table& card);

//---------------------void functions---------------------		
		
	 	void Deal(Table card[], Table player[], Table bot1[],Table bot2[],Table bot3[],Table bot4[],Table community[], user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_);
		void Sorting(Table sort[],int length);
		friend bool compare(Table sort[],int i);

//---------------------friend functions---------------------

//display		
	friend void Display(Table player[], Table community[], string roundName, double pot, double currentBet, user& bot1_, user& bot2_, user& bot3_,user& bot4_, user& player_);

//bot functions
		friend int botStrategy(Table botcheck[], int round);
		
//card functions		
		friend vector <int> Pairs(Table player[], Table community[]);
		friend vector <int> straightFlush(Table player[],Table community[]);
		friend int highCard(Table check[]);

		friend void firstPairs(Table player[], Table community[],vector <int>& firstP);
		friend void secondPairs(Table player[], Table community[],vector <int>& secondP);
		friend void extraPairs(Table player[], Table community[],vector <int>& extraP);
		friend void threeKind(Table player[],Table community[],vector <int>& threeK);
		friend void threeCom(Table player[], Table community[],vector <int>& threeC);
		friend void fourKind(Table player[],Table community[],vector <int>& fourK);
		
		friend void flush(Table player[], Table community[],vector<int>& flushIR );
		friend void straight(Table player[], Table community[],vector <int>& straight);
		
		//tie breaker
		vector<int> sortHands(vector<int> playerHand, vector <int> bot1Hand, vector <int> bot2Hand, vector <int> bot3Hand, vector <int> bot4Hand, user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_);
		vector<int> tieBreaker(int check[ROW][COL],int largest);
};
//functions to initialize deck 
void SetDeck(Table card[]);


//gives player round choices
void choice(double& pot, int round, double& currentBet, int& betCount, int& checkCount, int& countNeeded, bool& canCheck, user& player_);
void botChoice(double& pot, int round, double& currentBet, int& betCount, int& checkCount, int& countNeeded, bool& canCheck, user& bot_,  Table botcheck[]);


//various functions to determine if hands are present
void CheckWins(double pot, Table community[], Table player[], Table bot1[],Table bot2[],Table bot3[],Table bot4[], user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_);
vector <int> WinningHands(Table check[], Table community[]);


#endif
