#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string.h>
#include "user.h"
using namespace std;
//This class handles player attributes such as personal $ pot and names
user::user(){
	pot = 100.00;
	name = "names";
	isFold = false;
	isAllin = false;
	outofMoney= false;
	
}

//uses name file in project folder to randomize bot names
string user::setName(int max) {
   	string name;
    ifstream file;
    int i;
    
	file.open("5ltrNames.txt");
    for (i=0; i < max; i++){
		file >> name;
	}
    file.close();
	return name;
}

double user::updatePot(double pot, double bet)
{
	double newPot = pot - bet;
	return newPot;
}
