#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>
#include "deck.h"
#include "user.h"

using namespace std;

Table::Table()
{
	number = 0;
	suit = "?";
}

Table::Table(int num, string coat)
{
	number= num;
	suit = coat;
}

// Overloaded << to check cards
ostream& operator <<( ostream& couts, const Table& card)
{
	couts << "Number: " << card.number << " OF SUIT " << card.suit << endl;
	return couts;

}

//initializes cards
void SetDeck(Table card[])
{
	string suit;
	int i=0,y,z;
	for (z=1; z <=4; z++) {
		if(z==1) {
			suit = "H";
		}if(z==2) {
			suit = "D";
		}if(z==3) {
			suit = "S";
		}if(z==4) {
			suit = "C";
		}
		for ( y=2; y <= 14; y++) {
			card[i] = Table( y,suit);
			i++;
		}
	}
}



//deals cards to player, bot and community. Sets used card index to empty to prevent duplicates
//this works by randomizing index of array and setting that value equal to either player bot or community
//also serves as main gameflow function
void Table::Deal(Table card[], Table player[], Table bot1[],Table bot2[],Table bot3[],Table bot4[],Table community[], user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_)
{
	int j,max;
	string roundName;
	double currentBet =1, pot=100;
	bool canCheck = true;
	int betCount = 0, checkCount=0 , countNeeded = 5;
	
//	srand(time(0));
	j= (rand()%51);
	player[0] = card[j];
	card[j] = Table(0,"-");
//bot1 gets dealt 1st card
	do {
		j= (rand()%51);
		bot1[0] = card[j];
	} while(card[j].number == 0); 
//sets used card index to empty to prevent duplicates
	card[j] = Table(0,"-");

//bot2 gets dealt 1st card
	do {
		j= (rand()%51);
		bot2[0] = card[j];
	} while(card[j].number == 0); 
	card[j] = Table(0,"-");

//bot3 gets dealt 1st card
	do {
		j= (rand()%51);
		bot3[0] = card[j];
	} while(card[j].number == 0); 
	card[j] = Table(0,"-");

//bot4 gets dealt 1st card
	do {
		j= (rand()%51);
		bot4[0] = card[j];
	} while(card[j].number == 0); 
	card[j] = Table(0,"-");



//--------------------------------------------------------------second round of dealing
	do {
		j= (rand()%51);
		player[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	
	do {
		j= (rand()%51);
		bot1[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");

	do {
		j= (rand()%51);
		bot2[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	

	do {
		j= (rand()%51);
		bot3[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	
	do {
		j= (rand()%51);
		bot4[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	
	int round =-1;
	roundName = "Pre-flop";
	cout << "\t\t\t\t\t\t\t\t\t     STARTING BET IS :$" <<currentBet <<endl << endl;
	//---------------------------------Display table-------------------------------------------
	Display(player, community, roundName, pot, currentBet, bot1_, bot2_, bot3_, bot4_, player_);
	//----------------------
	while(player_.pot != 0 && bot1_.pot != 0 && bot2_.pot != 0 && bot3_.pot != 0 && bot4_.pot != 0)
	{	
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	choice(pot,round, currentBet, betCount, checkCount, countNeeded, canCheck, player_ );
	round = 0;
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot1_, bot1);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot2_, bot2);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot3_, bot3);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot4_, bot4);
		
	cout << "check count " << checkCount << " bet count"<< betCount << endl;
	cout << "count needed " << countNeeded << endl;
	// end loop when checkCount == 5 or betCount ==5
	}
	currentBet = 1;
	//----------------------
	do {

		j= (rand()%51);
		community[0] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");


	do {

		j= (rand()%51);
		community[1] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");


	do {

		j= (rand()%51);
		community[2] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");

	round = 1;
	roundName = "Flop";
	Display(player, community, roundName, pot, currentBet, bot1_, bot2_, bot3_, bot4_, player_);

	//----------------------
	betCount = 0;
	checkCount = 0;
	canCheck = true;
	while(player_.pot != 0 && bot1_.pot != 0 && bot2_.pot != 0 && bot3_.pot != 0 && bot4_.pot != 0)
	{	
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	choice(pot,round, currentBet, betCount, checkCount, countNeeded, canCheck, player_ );
	round = 0;
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot1_, bot1);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot2_, bot2);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot3_, bot3);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot4_, bot4);
		
	cout << "check count " << checkCount << " bet count"<< betCount << endl;
	cout << "count needed " << countNeeded << endl;
	// end loop when checkCount == 5 or betCount ==5
	}

	//----------------------
	do {

		j= (rand()%51);
		community[3] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	roundName = "Turn";
	Display(player, community, roundName, pot, currentBet, bot1_, bot2_, bot3_, bot4_, player_);
	round = 2;
	currentBet = 1;
	betCount = 0;
	checkCount = 0;
	canCheck = true;
	while(player_.pot != 0 && bot1_.pot != 0 && bot2_.pot != 0 && bot3_.pot != 0 && bot4_.pot != 0)
	{	
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	choice(pot,round, currentBet, betCount, checkCount, countNeeded, canCheck, player_ );
	round = 0;
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot1_, bot1);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot2_, bot2);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot3_, bot3);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot4_, bot4);
		
	cout << "check count " << checkCount << " bet count"<< betCount << endl;
	cout << "count needed " << countNeeded << endl;
	// end loop when checkCount == 5 or betCount ==5
	}
	

	//----------------------
	do {

		j= (rand()%51);
		community[4] = card[j];
	} while(card[j].number==0);
	card[j] = Table(0,"-");
	
	round = 3;
	currentBet = 1;
	betCount = 0;
	checkCount = 0;
	canCheck = true;
	roundName = "River";
	Display(player, community, roundName, pot, currentBet, bot1_, bot2_, bot3_, bot4_, player_);

	while(player_.pot != 0 && bot1_.pot != 0 && bot2_.pot != 0 && bot3_.pot != 0 && bot4_.pot != 0)
	{	
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	choice(pot,round, currentBet, betCount, checkCount, countNeeded, canCheck, player_ );
	round = 0;
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot1_, bot1);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot2_, bot2);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot3_, bot3);
		if(betCount == countNeeded || checkCount == countNeeded){
		break;
	}
	botChoice(pot, round, currentBet, betCount, checkCount, countNeeded, canCheck, bot4_, bot4);
	
	cout << "check count " << checkCount << " bet count"<< betCount << endl;
	cout << "count needed " << countNeeded << endl;
	// end loop when checkCount == 5 or betCount ==5
	}
	

	CheckWins( pot, community, player, bot1, bot2, bot3, bot4, player_, bot1_, bot2_, bot3_, bot4_);
	player_.isFold = false;
	player_.isAllin = false;
	bot1_.isFold = false;
	bot2_.isFold = false;
	bot3_.isFold = false;
	bot4_.isFold = false;
	
	if (player_.pot == 0)
	{
		cout << " It looks like you've run out money. Better luck Next time." << endl;
		exit(0);
	}
	
	if(bot1_.pot == 0)
	{
		cout<< bot1_.name << " is out of money and will recieving $100.00 to keep playing!" << endl;
		bot1_.pot = 100;
	}
	if(bot2_.pot == 0)
	{
		cout<< bot2_.name << " is out of money and will recieving $100.00 to keep playing!" << endl;
		bot2_.pot = 100;
	}
	if(bot3_.pot == 0)
	{
		cout<< bot3_.name << " is out of money and will recieving $100.00 to keep playing!" <<endl;
		bot3_.pot = 100;
	}
	if(bot4_.pot == 0)
	{
		cout<<  bot4_.name << " is out of money and will recieving $100.00 to keep playing!" <<endl;
		bot4_.pot = 100;
	}
}
//enters choice of player and performs accordingly. choices are controlled by switch statement.
void choice(double& pot, int round, double& currentBet, int& betCount, int& checkCount, int& countNeeded, bool& canCheck, user& player_)
{
		

	// Player variables
	int choice;
	double bet;
	
	if (player_.isFold == false&& player_.isAllin == false ) 
	{
		
			do
			{
				
				cout << "enter your choice: \n";
			if (round == -1 || canCheck == false)
			{
				cout << "1 for Call" << endl;
			}
			else
			{
				cout << "1 for Check" << endl;
			} 
				cout << "2 for Fold" << endl;
				cout << "3 for Raise" << endl <<endl;
		
				cin >> choice;
			if( choice < 0 || choice > 3){
					cout <<"Invalid choice. Please enter a number between 1 and 3.";
				}
			}while( choice < 0 || choice > 3); 
				
				switch (choice) {
				case 1:
					if (round == -1 || canCheck == false )
					{
						canCheck = false;
						if (currentBet > player_.pot)
						{
							cout << "Not enough money! You'll have to go all in." << endl;
							currentBet = player_.pot;
							player_.isAllin = true;
						}
						betCount += 1;	
						pot = pot + currentBet;
						player_.pot=player_.updatePot(player_.pot,currentBet);
						
						break;
					}
					else
					{
						checkCount += 1;
						canCheck = true;
						break;
					}
					case 2:
						cout << "Better luck next time!!!\n";
						countNeeded -= 1;
						player_.isFold = true;
						break;
					
					case 3:
						canCheck = false;								
						cout << "Enter the amount : \n";					
						cin >> bet;
						while (bet < 0.01)
						{
							cout << "Invalid bet, please enter a dollar amount higher than $0.00" << endl;
							cout << "Enter a valid amount : \n";
						cin >> bet;
						}
						while (bet <= currentBet)
						{
							cout<< "Your bet must be higher than the current bet to raise. "<< endl;
							cout<< "The current bet is: $" << currentBet << endl;
							cout << "Enter a higher amount : \n";
							cin >> bet;
						 } 
						while (bet > player_.pot)
						{
							cout << "Not enough money! Enter smaller amount.";
							cout << "Enter the amount : \n";
						cin >> bet;
						}
						
							if (bet == player_.pot)
							{
								cout << "ALL IN" << endl;
								player_.isAllin = true;
								
							}
						betCount = 0;
						betCount += 1;	
						currentBet=bet;
						pot +=  currentBet;
						player_.pot=player_.updatePot( player_.pot, currentBet);
						
						break;
		
			}
		}		
}

void botChoice(double& pot, int round, double& currentBet, int& betCount, int& checkCount, int& countNeeded, bool& canCheck, user& bot_,  Table botcheck[])
{
	
	// Player variables
	int choice=botStrategy(botcheck, round);
	double bet =1;

	
	if (bot_.isFold == false && bot_.isAllin == false) {
		
			switch (choice) {
	
				case 1:
				if (canCheck == false){
					canCheck = false;
					cout << bot_.name <<" is calling!" << endl;
					betCount +=1;
					if (currentBet > bot_.pot)
					{
						currentBet = bot_.pot;
						bot_.isAllin = true;
						cout << bot_.name <<"'s pot is too low  for current call, going all in!" << endl;
					}
					pot += currentBet;
					bot_.pot=bot_.updatePot(bot_.pot,currentBet);
					break;
				}
				else{
					cout << bot_.name << " is checking." << endl;
					checkCount += 1;
					canCheck = true;
					break;
				}	
					
				case 2:
					cout << bot_.name <<" is folding!" << endl;
					countNeeded -= 1;
					bot_.isFold = true;
					break;
				
				case 3:
					canCheck = false;
						while(bet <= currentBet)
						{
							bet+= 3;
						 } 
						

						while (bot_.pot - bet < 0)	
						{
							bet-=1;
						}
					
					if (bet == bot_.pot)
						{
							bot_.isAllin = true;
						}
					cout << bot_.name <<" is raising to "<< bet << " ! " << endl;
					betCount = 0;
					betCount += 1;
					currentBet=bet;
					pot +=  currentBet;
					bot_.pot=bot_.updatePot( bot_.pot, currentBet);
					break;
				default:
					cout << "unknown play by " << bot_.name << endl;
			}
		}

			
}

// Determine bot strategy base strictly on the cards they hold
int botStrategy(Table botcheck[], int round){
		int largest=0;
	int random=0;
	srand(time(0));
	//Sort bot hands before check
	Table temp[1];
	largest = botcheck[0].number;
	if(largest > botcheck[1].number){
		temp[0] = botcheck[1];
		botcheck[1] = botcheck[0];
		botcheck[0] = temp[0];
		
	}
	// Paired hands
	if( botcheck[0].number == botcheck[1].number && botcheck[0].number > 11){
		random = (rand() %101) +1;
		if(random < 6 || random == 8){
			return 3;
		}
		else
			return 1;
		//no fold here
	}
	if( botcheck[0].number == botcheck[1].number && botcheck[0].number > 7){
		random = (rand() %10) +1;
		if(random < 6){
			return 3;
		}
		if (random == 10){
			return 2;
			// fold but very low chance of happening
		}
		else 
			return 1;
		
	}
	if( botcheck[0].number == botcheck[1].number && botcheck[0].number ){
		random = (rand() %10) +1;
		//25raise/75call
		if(random <7){
			return 1;
		}
		else 
			return 3;
	}
	// Non-paired hands(off suit)
	if( botcheck[0].number == 2 && botcheck[1].number == 6){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;	
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 2 && botcheck[1].number == 7){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;	
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 2 && botcheck[1].number == 8){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 2 && botcheck[1].number == 9){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 2 && botcheck[1].number == 10){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 3 && botcheck[1].number == 6){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 3 && botcheck[1].number == 7){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 3 && botcheck[1].number == 8){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 3 && botcheck[1].number == 9){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 4 && botcheck[1].number == 7){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 4 && botcheck[1].number == 8){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 4 && botcheck[1].number == 9){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 5 && botcheck[1].number == 8){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number == 5 && botcheck[1].number == 9){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number <10 && botcheck[1].number >10){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %5) +1;
			//85call/15fold
			if(random < 7){
			return 1;
		}
		else
			return 2;
		
		}
	}if( botcheck[0].number <10 && botcheck[1].number ==14){
		if( botcheck[0].suit != botcheck[1].suit){
			random = (rand() %10) +1;
			//90call/10fold
			if(random < 10){
				return 1;
			}
			else 
				return 2;
		}
	}
	
	random = (rand() %3) +1;
	int i=0;
	int total=0;
	switch(random){
		case 1:
			//high card value
			total = botcheck[0].number + botcheck[1].number;
			// 14 and 2
			if(total >= 16){
				i = (rand() % 5) +1;
				for(int j = 0 ; j <2 ; j++){
					if (botcheck[j].number == 14){
						if(i == 1 || i == 5 || i ==3){
							return 1;
						} 
						if(i == 4){
							return 3;
						}
						else
							return 2;						
					}
					if(botcheck[j].number >10){
						if(i == 1){
							return 2;
						} 
						else
							return 1;					
					
					}
					else
						return 1;
				}
			}
			else{
				i = (rand() % 5) +1;
			
				if ( i  <5){
					return 1;
				}
				else 
					return 2;
			}
			

		case 2:
			total = botcheck[0].number - botcheck[1].number;
			i = (rand() %8) +1;

			if(total == 3 | total == -3){
				if( botcheck[0].number > 5){
					
					if ( i==1 || i == 3|| i ==5 || i == 7){
						return 1;
					}if (i ==4 || i == 2){
						return 2;
					}
					else 
						return 3;
				}
				if( botcheck[0].number <= 5){	
					if (i == 3|| i ==5 || i == 7){
						return 1;
					}if ( i == 2){
						return 2;
					}
					else 
						return 3;			
				}
			}if(total == 2 | total == -2){
				if( botcheck[0].number <= 5){
					if ( i == 1|| i == 3|| i ==5 || i == 7){
						return 1;
					}if ( i == 2){
						return 2;
					}
					else 
						return 3;
				}if( botcheck[0].number > 5){
					if ( i == 3|| i ==5 || i == 7){
						return 1;
					}
					else 
						return 3;
				}
			}if(total == 1 | total == -1){
				if( botcheck[0].number >= 10 || botcheck[1].number >= 10){
					return 3;
				}if( botcheck[0].number < 10 || botcheck[1].number < 10 ){						
					if (i ==5 || i == 7){
						return 1;
					}
					else 
						return 3;		
				}
			}
			else{
				if (i ==5 || i == 7){
					return 2;
				}
				else
					return 1;					
			}
		case 3:
		//suited ness
		if( botcheck[0].suit == botcheck[1].suit){
			int total;
			i = (rand() %8) +1;
			total = botcheck[0].number - botcheck[1].number;
			if(total == 2 | total == -2){
					if( botcheck[0].number <= 5){
						if ( i == 3|| i ==5 || i == 7){
							return 1;
						}
						else 
							return 3;
					}
					if( botcheck[0].number > 5){
						if ( i == 3|| i ==5 || i == 7){
							return 1;
						}
						else 
							return 3;
					}
					
					
			}if(total == 1 | total == -1){
				if( botcheck[0].number >= 8 || botcheck[1].number >= 8){
					return 3;
				}if( botcheck[0].number < 8 || botcheck[1].number < 8 ){						
					if (i ==5 || i == 7){
						return 1;
					}
					else 
						return 3;		
					}
			
			}
			else{
						if (i==1||i ==3|| i ==5 || i == 7){
							return 1;
						}
						if(i==2 || i == 4) {
							return 2;
						}
						else
							return 3;	
									
					}
		}
		else {
			i = (rand() %10)+1;
				total = highCard(botcheck);
				if(total >= 11){
					if(i == 1|| i == 3|| i == 5|| i == 7|| i == 9){
						return 1;
					}
					if(i == 2|| i == 4|| i == 6){
						return 2;
					}
					else 
						return 3;
					
				}
				else{
					if(i == 1|| i == 3|| i == 5|| i == 7|| i == 9){
						return 2;	
					}
					if(i == 2|| i == 4|| i == 6){
						return 1;
					}
					else 
						return 3;
				}
			
		}
	
	}

}

// Check for kicker if there's a tie to determine winner
vector<int> tieBreaker(int check[ROW][COL],int largest){
	int largest1, largest2;
	int counter1 = 0,counter2 =0;
	int j=0;
	vector <int> winner(2);
	//check for second value

	for(int i = 0; i < COL ; i++){
		if(check[1][i] == 1){
			largest1 = check[3][i];
			break;
		}
	} 

	
	for(int i = 0; i < COL ; i++){
		if ( check[3][i] > largest1 && check[1][i] == 1 ){
			largest1 = check[3][i];
		}
	}
		for(int i = 0; i < COL ; i++){
	if(check[3][i] == largest1 ){
			counter1 += 1;		
		}
	}
	if ( counter1 == 1){
		for(int i= 0 ; i < COL; i++){
			if (check[3][i] == largest1 && check[1][i] == 1){
				winner[0] = check[0][i];
				winner[1] = check[0][i];
				return winner;	
			}
		}
	}
	//check for third value
	for(int i = 0; i < COL ; i++){
		if(check[1][i] == 1){
			largest2 = check[4][i];
			break;
		}
	}
	for( int i= 0; i <COL ; i++){
		if (check[4][i] > largest2 && check[1][i] ==1){
			largest2 = check[4][i];
			}
	}
	for( int i= 0; i <COL ; i++){
		if(check[4][i] == largest2){
			counter2 += 1;
		}
	}
	if ( counter2 == 1){
		for(int i= 0 ; i < COL; i++){
			if (check[4][i] == largest2 && check[1][i] == 1){
				winner[0] = check[0][i];
				winner[1] = check[0][i];
				return winner;	
			}
		}
	}
	else 
	for(int i = 0; i < COL ; i ++){
		if (check[4][i] == largest2 && check[1][i] == 1){
			winner[j] =check[0][i];
			j++;
		}
		
	}
	return winner;
}

// Sort check to see which hands has higher value if there's a tie. If there's more to evaluate, then call tieBreaker 
vector <int> sortHands(vector<int> playerHand, vector <int> bot1Hand, vector <int> bot2Hand, vector <int> bot3Hand, vector <int> bot4Hand, user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_){
	vector <int> winner(2);
	int i, counter = 0, j =0, largest=0;
	largest =playerHand[0]; 
	int check[5][5];
	if(bot1Hand[0] > largest){
		largest = bot1Hand[0];
	}
	if(bot2Hand[0] > largest){
		largest = bot2Hand[0];
	}
	if(bot3Hand[0] > largest){
		largest = bot3Hand[0];
	}
	if(bot4Hand[0] > largest){
		largest = bot4Hand[0];
	}
	for( i = 0 ; i <5 ; i++){
		check[0][i] = (i+1);
	}
	// check to see if player's hands = to largest
	if(playerHand[0] == largest){
		check[1][0] =1;
		counter += 1;
	}if(bot1Hand[0] == largest){
		check[1][1] =1;
		counter += 1;
	}if(bot2Hand[0] == largest){
		check[1][2] =1;
		counter += 1;
	}if(bot3Hand[0] == largest){
		check[1][3] =1;
		counter += 1;
	}if(bot4Hand[0] == largest){
		check[1][4] =1;
		counter += 1;
	}
	//if there's only one largest then return the winner now
	if(counter ==1){
		for( i = 0 ; i <5; i++){
			if (check[1][i] == 1 ){
				winner[0] = check[0][i];
				winner[1] = check[0][i];
				return winner;
			}
		}
	}
	//if not then keep finding
	for(i = 2; i <5;i++){
		check[i][0] =  playerHand[j];
		j++;
		
	}
	j =0;
	for(i = 2; i <5;i++){
		check[i][1] =  bot1Hand[j];
		j++;
	}
	j =0;
	for(i = 2; i <5;i++){
		check[i][2] =  bot2Hand[j];
		j++;
	}
	j =0;
	for(i = 2; i <5;i++){
		check[i][3] =  bot3Hand[j];
		j++;
	}
	j =0;
	for(i = 2; i <5;i++){
		check[i][4] =  bot4Hand[j];
		j++;
	}

	// get final winner
	winner = tieBreaker(check, largest);
	
	return winner;
}

// Settle, announce, and give pot to winner.
void CheckWins(double pot, Table community[], Table player[], Table bot1[],Table bot2[],Table bot3[],Table bot4[], user& player_, user& bot1_, user& bot2_, user& bot3_, user& bot4_){
	vector <int> playerHand(3), bot1Hand(3), bot2Hand(3), bot3Hand(3), bot4Hand(3);
    playerHand = WinningHands(player, community);
	bot1Hand = WinningHands(bot1, community);
	bot2Hand = WinningHands(bot2, community);
	bot3Hand = WinningHands(bot3, community);
	bot4Hand = WinningHands(bot4, community);
	vector<int> winNum(2);
	string winner;
	int count =0, result;
	winNum = sortHands(playerHand, bot1Hand, bot2Hand,  bot3Hand,  bot4Hand, player_, bot1_, bot2_, bot3_, bot4_);
	cout << playerHand[0] <<" is the player hand value" <<endl;
	cout <<endl;
	cout <<	bot1Hand[0]   <<" is the bot1 hand value"   <<endl;
	cout <<endl;
	cout <<	bot2Hand[0]   <<" is the bot2 hand value"   <<endl;
	cout <<endl;
	cout <<	bot3Hand[0]   <<" is the bot3 hand value"   <<endl;
	cout <<endl;
	cout <<	bot4Hand[0]   <<" is the bot4 hand value"   <<endl;
	cout <<endl;
	
	cout << "player: " <<endl;
	for(int i = 0; i <playerHand.size() ; i++){
		cout <<playerHand[i] << "  " ;
	}
	cout << endl <<bot1_.name <<endl;
	for(int i = 0; i <2;i++){
		cout << bot1[i] <<endl;	
	}
	for(int i = 0; i <bot1Hand.size() ; i++){
		cout <<bot1Hand[i] << "  " ;
	}
	cout << endl <<bot2_.name <<endl;
	for(int i = 0; i <2;i++){
		cout << bot2[i] <<endl;	
	}
	for(int i = 0; i <bot2Hand.size() ; i++){
		cout <<bot2Hand[i] << "  ";
	}
	cout << endl <<bot3_.name <<endl;
	for(int i = 0; i <2;i++){
		cout << bot3[i] <<endl;	
	}
	for(int i = 0; i <bot3Hand.size() ; i++){
		cout <<bot3Hand[i] << "  ";
	}
	cout << endl << bot4_.name <<endl;
	for(int i = 0; i <2;i++){
		cout << bot4[i] <<endl;	
	}
	for(int i = 0; i <bot4Hand.size() ; i++){
		cout <<bot4Hand[i] << "  ";
	}
	//(1,4)
	result = static_cast<double>(pot);
	if ( result % 2 == 0){
	pot = pot/2.0;
	}
	else{
		pot +=1;
		pot = pot/2.0;
	}
	do
	{
		result = winNum[count];
		switch(result) {
	
				case 1:
					player_.pot += pot;
					count +=1;
					break;
				case 2:
					bot1_.pot += pot;
					count +=1;
					break;
	
				case 3:
					bot2_.pot += pot;
					count +=1;
					break;
				case 4:
					bot3_.pot += pot;
					count +=1;
					break;
	
				case 5:
					bot4_.pot += pot;
					count +=1;
					break;
				
				default: 
				cout << "cannot determine winner" << endl;
				break;
		}
	}while(count != 2);
	if(winNum[0] ==winNum[1] && winNum[0] == 1){
		winner = "Player";
		cout << endl << winner << " is the winner of this round."<< endl;
	}
	if(winNum[0] ==winNum[1] && winNum[0] == 2){
		winner = bot1_.name;
		cout << endl << winner << " is the winner of this round."<< endl;
	}
	if(winNum[0] ==winNum[1] && winNum[0] == 3){
		winner = bot2_.name;
		cout << endl << winner << " is the winner of this round."<< endl;
	}
	if(winNum[0] ==winNum[1] && winNum[0] == 4){
		winner = bot3_.name;
		cout << endl << winner << " is the winner of this round."<< endl;
	}
	if(winNum[0] ==winNum[1] && winNum[0] == 5){
		winner = bot4_.name;
		cout << endl << winner << " is the winner of this round."<< endl;
	}
	if(winNum[0] != winNum[1]){
		string winner1, winner2;
		int i,j=0;
		cout << "The pot is split" << endl;
		for(i = 0; i <3; i++){
			if(winNum[i] == 1){
				winner = "Player";
			}
			if(winNum[i] == 2){
				winner = bot1_.name;
			}
			if(winNum[i] == 3){
				winner = bot2_.name;
			}
			if(winNum[i] == 4){
				winner = bot3_.name;
			}
			if(winNum[i] == 5){
				winner = bot4_.name;
			}
			cout << "Winner#" << i+1 << " is " << winner << endl;
			j++;
			if (j == 2){
			 	break;
			 }
		}
		
	}
	 
}

// Check for hands values. Highest values = better hand.
vector<int> WinningHands(Table check[],Table community[]){
	vector<int> largest(3);
	largest = Pairs(check,community);
	vector<int> temp(3);
	temp = straightFlush(check,community);
	
	if( largest[0]> temp[0]){
		return largest;
	}
	else
	return temp;
																																//10 is royal flush
																																//9  is straight flush
																																//8 is four of a kind
																																//7 is full house
																																//6 is flush
																																//5 is straight
																																//4 is three of a kind
																																//3 is two pairs
																																//2 is one pair
																																//1 is high card
}

//sort function for the card arrays
void Sorting(Table sort[],int length){
	int i;
	Table temp[1];
	
	for ( i = length - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (compare(sort,j)) {
				temp[0] = sort[j+1];
				sort[j+1] = sort[j];
				sort[j] = temp[0];
			}
		}
	}
}

// find if object[i].number > object[i+1].number
bool compare(Table sort[],int i){
	return(sort[i].number > sort[i+1].number);
}

// return highest card value in player's hand.
int highCard(Table player[]){
	
	int largest;
	largest = player[0].number;
	if ( player[1].number > player[0].number){
		largest = player[1].number;
	}

return largest;
}

// see if first card macthes with community
void firstPairs(Table player[], Table community[],vector <int>& firstP){
// 2 3 | 2 9 8 5 4
		for (int j=0 ; j<5 ; j++) {
			if (player[0].number == community[j].number ) {
				firstP[0] = 1 ;
				firstP[1] = player[0].number;
				
			}
		}
	
}

// see if second card matches with community
void secondPairs(Table player[], Table community[], vector <int>& secondP){
// 2 3 | 2 9 8 5 4
		for (int j=0 ; j<5 ; j++) {
			if (player[1].number == community[j].number ) {
				secondP[0] =1;
				secondP[1] = player[1].number;
			}
	
	}
		//false
}

// see if community has a pair that doesn't match with player
void extraPairs(Table player[], Table community[],vector <int>& extraP){
	// 2 3 | 2 2 4 5 5
	// i
	//             j
	//               
	int temp;
	int k = 0;
	bool first =false,second = false;
	for (int j=0 ; j<5 ; j++) {
		if (player[0].number != community[j].number && community[j].number == community[j+1].number) {
			first = true;
			temp = community[j].number;
			break;
		}
	}
	for (int j=0 ; j<5 ; j++) {
		if (player[1].number != community[j].number && community[j].number == community[j+1].number) {
			second = true;
		}		
	}
	if(first & second){
		extraP[0] = 1;
		extraP[1] = temp;
	}

	//false
}

//see if community has Three of a Kind
void threeCom(Table player[],Table community[],vector <int>& threeC){
	int i,j,k,x;
	Sorting(community,5);
	// 4 3 |  2 2 2 4 6
	// i
	//        j
	//          k
	//            x
	for ( i=0 ; i<2 ; i++) {
		for( j = 0; j<5;j++){
			if (player[i].number != community[j].number && community[j].number == community[j+1].number && community[j+1].number == community[j+2].number){
				threeC[0] =1;
				threeC[1] = community[j].number;
					}
				}
			}
}

//see if player has Three of a Kind when combines with community
void threeKind(Table player[], Table community[], vector <int>& threeK){
	// 2 3 | 2 2 4 5 6
	int i,j;
	    Sorting(community,5);
	for ( i=0 ; i<2 ; i++) {
		for (j=0 ; j<5 ; j++) {
			
				if (player[i].number ==community[j].number && community[j].number == community[j+1].number){
					threeK[0] = 1;
					threeK[1] = community[j].number;
			}
		}
	}
	//false
}

// see if player has Four of a Kind when combines with community
void fourKind(Table player[],Table community[], vector <int>& fourK){
	int i,j;
	
	Sorting(community,5);
	// 2 3 |  2 2 2 4 6
	// i
	//        j
	//          k
	//            x
	for ( i=0 ; i<2 ; i++) {
		for ( j=0 ; j<5 ; j++) {
							
					if (player[i].number == community[j].number && community[j].number == community[j+1].number && community[j].number == community[j+2].number){
						fourK[0] = 1;
						fourK[1] = player[i].number;
					}	
			}
	}
	//false
	
}

//check for Four of a Kind, Full House, Three of a Kind, Two Pairs, One Pair, High Card and return hand values respectively
vector<int> Pairs(Table player[],Table community[]){
	vector <int> firstP(2);
	vector <int> secondP(2);
	vector <int> threeK(2);
	vector <int> threeC(2);
	vector <int> extraP(2);
	vector <int> fourK(2);
	vector <int> final(3);
	firstPairs(player, community, firstP);
	secondPairs(player, community, secondP);
	extraPairs(player, community, extraP);
	threeKind(player, community, threeK);
	threeCom(player, community, threeC);
	fourKind(player, community, fourK);
	int i,j, handValue=0;
	bool have_pairs = false;
	if (player[0].number == player[1].number) {
		have_pairs = true;
	}
	Sorting(community,5);
	if (have_pairs) {
	
		//if (threeKind(player,community)){
		if (threeK[0] == 1){
			//return 8;
			final[0] =8;
			final [1] = threeK[1];
			return final;
		}
		//if(threeCom(player,community)){
		if(threeC[0] == 1){
			final[0] = 7;
			final[1] =threeC[1];
			final[2] = player[0].number;
			return final;
			//return 7;
		}
		//if (firstPairs(player,community) && extraPairs(player,community)){
		if(firstP[0] == 1 && extraP[0] == 1){
			final[0] = 7;
			final[1] = firstP[1];
			final[2] = extraP[1];
			return final;
			//return 7;
		}
		//if (firstPairs(player,community)){
		if(firstP[0] == 1){
			final[0] = 4;
			final[1] =firstP[1];
			return final;
			//return 4;
		}
		//if (extraPairs(player,community)){
		if(extraP[0] == 1){
			final[0] = 3;
			if(player[0].number > extraP[1])
			{
				final[1]= player[0].number;
				final[2] = extraP[1];
				return final;
			}
			
			final[1] = extraP[1];
			final[2] = player[0].number;
			//return 3;
			return final;
		}
		else {
			final[0] = 2;
			final[1] = player[0].number;
			return final;
			//return 2;
		}
	}
	if (!have_pairs) {
		//if(fourKind(player,community)){
		if(fourK[0]==1){
			//2 3 | 2 2 2 5 6
			final[0] = 8;
			final[1] = fourK[1];
			return final;
			//return 8;
		}
		//if(threeKind(player,community) && extraPairs(player,community)){
		if(threeK[0] == 1 && extraP[0] == 1){
			if( threeK[1] != extraP[1]){
			// 2 4 | 2 2 4  (5 5)
			final[0] = 7;
			final[1] = threeK[1];
			final[2] = extraP[1];
			cout <<"the first one" << endl;
			return final;
			//return 7;
			}
		}
		//if(threeKind(player,community) && firstPairs(player ,community)){
		if(threeK[0] == 1 && firstP[0] == 1){
			if(threeK[1] != firstP[1]){
			// 2 3 | 2 3 3 5 8
			final[0] = 7;
			final[1] = threeK[1];
			final[2] = firstP[1];
			cout <<"the second one 1"<<endl;
			return final;
			//return 7;
			}
		}
		//if(threeKind(player,community) && secondPairs(player ,community)){
		if (threeK[0]== 1 && secondP[0] == 1 ){
			if(threeK[1] != secondP[1]){
			// 3 2 | 2 3 3 5 8
			final[0] = 7;
			final[1] = threeK[1];
			final[2] = secondP[1];
			cout <<"the second one 2"<<endl;
			return final;
			//return 7;
			}
		}
		//if(firstPairs(player ,community) && threeCom(player,community)){
		if(firstP[0] == 1 && threeC[0] == 1){
			
			// 2 3 | 2 4 4 4 5
			final[0] = 7;
			final[1] = threeC[1];
			final[2] = firstP[1];
			cout <<"the third one 1"<<endl;
			return final;
			//return 7;
		}
		//if(secondPairs(player ,community) && threeCom(player,community)){
		if(secondP[0] == 1 && threeC[0] ==1){
			final[0] = 7;
			final[1] = threeC[1];
			final[2] = secondP[1];
			cout <<"the third one 2"<<endl;
			return final;
			//return 7;
		}
		//if(threeKind(player,community)){
		if(threeK[0]==1){
			final[0] = 4;
			final[1] = threeK[1];
			final[2] = highCard(player);
			return final;
			//return 4;
		}
		//if (firstPairs(player,community) && extraPairs(player,community)){
		if(firstP[0] == 1 && extraP[0] == 1){
			final[0] = 3;
			if(firstP[1] > extraP[1]){
				final[1] = firstP[1];
				final[2] = extraP[1];
				return final;
			}
			final[1] = extraP[1];
			final[2] = firstP[1];
			return final;
			//return 3;
		}
		//if (secondPairs(player,community) && extraPairs(player,community)){
		if(secondP[0] == 1 && extraP[0] == 1){
			final[0] = 3;
			if(secondP[1] > extraP[1]){
				final[1] = secondP[1];
				final[2] = extraP[1];
				return final;
			}
			final[1] = extraP[1];
			final[2] = secondP[1];
			return final;
			//return 3;
		}
		//if(firstPairs(player,community) && secondPairs(player,community)){
		if(firstP[0] == 1 && secondP[0] == 1){
			if(firstP[1] != secondP[1]){
				cout << "This second one"<<endl;
				final[0] = 3;
				if(firstP[1] > secondP[1]){
					final[1] = firstP[1];
					final[2] = secondP[1];
					return final;
				}
				final[1] = secondP[1];
				final[2] = firstP[1];
				return final;
			}
			//return 3;
		}
		//if (firstPairs(player, community)||secondPairs(player,community)) {
		if(firstP[0] == 1 || secondP[0] == 1){
			final[0] =2;
			if(firstP[0] == 1){
				final[1] = firstP[1];
				return final;
			}
			final[1] = secondP[1];
			return final;
			//return 2;
		}

}
	final[0]= 1;
	final[1] = highCard(player);
	return final;
	//return 1;
}

// see if player has Flush when combines with community
void flush(Table player[], Table community[],vector<int>& flushIR ){
		int const length = 7;
		int i, hCount =0, dCount=0, sCount=0, cCount=0; 
		string completeHand[length];
		for (i = 0; i < 5; i++) {
			completeHand[i] = community[i].suit;
		}
			completeHand[5] = player[0].suit;
			completeHand[6] = player[1].suit;

	for (i = 0; i < length; i++) {	
		if (completeHand[i] =="H"){
			hCount += 1;
		}if (completeHand[i] =="D"){
			dCount += 1;
		}if (completeHand[i] =="S"){
			sCount += 1;	
		}if (completeHand[i] =="C"){
			cCount += 1;
		}
	}
	if(hCount > 4){
		if(player[0].suit == "H"|| player[1].suit == "H"){
			flushIR[0] =1;
		}	
	}if(dCount > 4){
		if(player[0].suit == "D"|| player[1].suit == "D"){
			flushIR[0] =1;
		}	
	}if(sCount > 4){
		if(player[0].suit == "S"|| player[1].suit == "S"){
			flushIR[0] =1;
		}	
	}if(cCount > 4){
		if(player[0].suit == "C"|| player[1].suit == "C"){
			flushIR[0] =1;
		}	
	}
	
}

// see if player has Straight when combines with community
void straight(Table player[], Table community[],vector <int>& straight){
	int smallest = 15;
	int count = 1;
	int cardDifference, i , j;
	int const length = 7;
	Table completeHand[length];
	vector<int> straightHand;
	for (i = 0; i < 5; i++) {
		completeHand[i] = community[i];
	}
	
	completeHand[5] = player[0];
	completeHand[6] = player[1];
	
	Sorting(completeHand, length);
	
	//checks for straight (5 consecutive cards regardless of suit)
	// works by sorting then subtracting values 'next" to each other and if result is 1 then cards are consecutive.
	for (i = 6; i > -1; i--) {
		
		cardDifference = completeHand[i].number - completeHand[i-1].number;
		if (cardDifference == 1){
			smallest = completeHand[i-1].number;
			straightHand.push_back(completeHand[i].number);
			count += 1;
			if(count >= 5){
				break;
			}
		}
		else
		{
		count = 1;
		straightHand.clear();	
		}
	}
	straightHand.push_back(smallest);


	if (straightHand.size() >= 5){
		for (i = 0 ; i < straightHand.size(); i++){
			if (straightHand[i]==player[0].number)
				//return true;
				straight[0] = 1;
				straight[1] = straightHand[0];					
		}
		
		for (i = 0 ; i < straightHand.size(); i++){
			if (straightHand[i]==player[1].number)
				//return true;
				straight[0] = 1;
				straight[1] = straightHand[0];	
		}
	} 
}

//check for Royal Flush, Straight Flush, Flush, Straight and return hand values respectively
vector<int> straightFlush(Table player[], Table community[]){
	vector<int>straightC(2);
	vector<int>flushIR(2);
	vector<int>result(3);
	straight(player,community,straightC);
	flush(player,community,flushIR);
	//if(straight(player,community,straight) && flush(player,community)){
		//if royal flush (0.000154%), return 10
		if(straightC[0] == 1 && flushIR[0] == 1){
			if(straightC[1] == 14){
				result[0] = 10;
				return result;
			}
			result[0] =9;
			return result;
			
		}
		if(flushIR[0] == 1){
			result[0] = 6;
			result[1] = highCard(player);
			return result;
		}
		if(straightC[0] == 1){
			result[0] =5;
			result[1] = straightC[1];
			result[2] = highCard(player);
			return result;
		}
		
		return result;
}

//main display table function
void Display(Table player[], Table community[], string roundName, double pot, double currentBet, user& bot1_, user& bot2_, user& bot3_,user& bot4_, user& player_)
{

	int i;
	
	cout <<"\t\t\t\t" <<"                      ___________________________________________________________________ \n";
	cout <<"\t\t\t\t" <<"                     /                                Pot:                               \\                  \n";
	if (pot >=10 && pot <=99){
		cout <<"\t\t\t\t" <<"                    /                                  $"<<pot<<"                                \\                 \n";
	}
	else if (pot >= 100){
		cout <<"\t\t\t\t" <<"                    /                                $"<<pot<<"                                 \\                 \n";
	}
	else{
	
	cout <<"\t\t\t\t" <<"                    /                                  $"<<pot<<"                                 \\                 \n";
	} 
	cout <<"\t\t\t\t" <<"          "<<bot2_.name<<"    /                                                                       \\     "<<bot3_.name<<"              \n";
	cout <<"\t\t\t\t" <<"           $"<< setw(3)<<bot2_.pot << "   /                                                                         \\     " <<"$"<<setw (3)<< bot3_.pot<< "  \n";
	cout <<"\t\t\t\t" <<"                 /                                                                           \\              \n";
	cout <<"\t\t\t\t" <<"                /                                                                             \\             \n";
	cout <<"\t\t\t\t" <<"               /                                                                               \\            \n";
	cout <<"\t\t\t\t" <<"              /                                                                                 \\           \n";
	cout <<"\t\t\t\t" <<"             /                                                                                   \\          \n";
	cout <<"\t\t\t\t" <<"            /                                                                                     \\         \n";
	cout <<"\t\t\t\t" <<"           /                                                                                       \\        \n";
	cout <<"\t\t\t\t" <<"          /                                                                                         \\       \n";
	cout <<"\t\t\t\t" <<"         /                                                                                           \\      \n";	
	cout <<"\t\t\t\t" <<"        /                                      Community Cards:                                       \\     \n";
	cout <<"\t\t\t\t" <<"       /                                    ___  ___  ___  ___  ___                                    \\    \n";	
	
		cout << "\t\t\t\t" <<"      | \t\t\t           ";
		for (i = 0; i <5 ; i ++){
			cout<< "| ";
			if(community[i].number == 0 ){
			 cout << " "<<" " << "|";
			}
			else if(community[i].number >= 10 ){
			 cout <<community[i].number << "|";
			}
			else
			cout <<community[i].number<<" " << "|";
		} 
		cout <<"\t\t\t\t        |" << endl;
		cout <<"\t\t\t\t" << "      | \t\t\t           ";
		for (i = 0; i <5 ; i ++){
			cout<< "| " ;
			if(community[i].suit == "" ){
			 cout << " " << " |";
			}
			else
			cout << community[i].suit <<" " << "|";	
		}
		cout << "\t\t\t\t        |" << endl;
		cout <<"\t\t\t\t" << "      | \t\t\t           ";
		for (i = 0; i <5 ; i ++){
			cout<< "|___|";	
		}
		cout << "\t\t\t\t        |" << endl;
		
	cout <<"\t\t\t\t" <<"       \\                                                                                               /            \n";
	cout <<"\t\t\t\t" <<"        \\                                                                                             /            \n";
	cout <<"\t\t\t\t" <<"         \\                                      Round: "<<setw(8)<<left<<roundName <<"                                      /            \n";
	cout <<"\t\t\t\t" <<"          \\                                                                                         /            \n";
	cout <<"\t\t\t\t" <<"           \\                                                                                       /            \n";
	cout <<"\t\t\t\t" <<"            \\                                                                                     /            \n";
	cout <<"\t\t\t\t" <<"             \\                                                                                   /            \n";
	cout <<"\t\t\t\t" <<"              \\                                                                                 /            \n";
	cout <<"\t\t\t\t" <<"               \\                                                                               /            \n";
	cout <<"\t\t\t\t" <<"                \\                                                                             /             \n";
	cout <<"\t\t\t\t" <<"                 \\                                                                           /              \n";
	cout <<"\t\t\t\t" <<"                  \\                                                                         /               \n";
	cout <<"\t\t\t\t" <<"          "<<bot1_.name<<"    \\                                                                       /    "<<bot4_.name<<"     \n";
	cout <<"\t\t\t\t" <<"           $"<< setw(3)<<bot1_.pot << "     \\                                                                     /     " <<"$"<<setw (3)<< bot4_.pot<< "  \n";

	cout <<"\t\t\t\t" <<"                     \\___________________________________________________________________/                  \n";
	

	cout <<"\t\t\t\t  " <<"                                                   Player                                                   \n";
	cout <<"\t\t\t\t  " <<"                                                    $" << player_.pot<<"                                                    \n";
	cout <<"\t\t\t\t  "<<"                                                 ___    ___                                                \n";

		
	cout <<"\t\t\t\t  " << "\t\t\t\t\t        ";
		for (i = 0; i <2 ; i ++){
			cout<< "  | " ;
			if(player[i].number >= 10 ){
			 cout << player[i].number <<"|";
			}	
			else{
			cout << player[i].number <<" " << "|";
			}
		} 
		cout <<"\t\t\t\t  " << "\t\t\t\t       " << endl;
		
		cout <<"\t\t\t\t  " <<"\t\t\t\t\t        ";
		for (i = 0; i <2 ; i ++){
			cout<< "  | " << player[i].suit <<" " << "|";	
		}
		cout << "\t\t\t\t       " << endl;
		cout <<"\t\t\t\t  " << "\t\t\t\t\t        ";
		for (i = 0; i <2 ; i ++){
			cout<< "  |___|";	
		}
		cout << "\t\t\t\t      " << endl;
}

