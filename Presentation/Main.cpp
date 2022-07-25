#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string.h>



#include "deck.h"
#include "Menu.h"
#include "user.h"

const int MAX = 2;
int maximum = 0;
using namespace std;



	
int main()
{
user player_;
user bot1_;
user bot2_;
user bot3_;
user bot4_;

	srand(time(0));
  
		maximum = (rand() % 97)+1;
		bot1_.name = bot1_.setName(maximum);
		
	    maximum = (rand() % 97)+1;
		bot2_.name = bot2_.setName(maximum);
		
	    maximum = (rand() % 97)+1;
		bot3_.name = bot3_.setName(maximum);
		
	    maximum = (rand() % 97)+1;
		bot4_.name = bot4_.setName(maximum);
	
	char playAgain = 'y';

		Menu start; //begins a menu object- gives options to user-check Menu.h for details
		start.opening();
		start.input(cin);
	do{ //everything past this point changes/initalizes per game		
		Table card[51];
		Table community[5];
	//PLAYER CARD ARRAY	
		Table player[MAX];
		Table bot1[MAX];
		Table bot2[MAX];
		Table bot3[MAX];
		Table bot4[MAX];
			
		Table deal;
		//initializing the cards
		SetDeck(card);
	
	
		deal.Deal(card,player, bot1, bot2, bot3, bot4,community, player_, bot1_, bot2_, bot3_, bot4_);
	
			cout <<"Would you like to play again? Enter 'y' to continue, any other key exits" << endl;
				cin >> playAgain;
		
	}while(playAgain == 'y' || playAgain =='Y');
	
system("pause");
return 0;
};
