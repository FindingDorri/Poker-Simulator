#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace std;


Menu::Menu() {
	choice=0;
	check = false;
}

void Menu::output(ostream& couts) {
	cout<< "******************************************" <<endl;
	cout<< "\tWelcome to High Stakes Poker" << endl;
	cout << endl;
	cout<< "1.Start Game." <<endl;
	cout<< "2.Game rules." <<endl;
	cout<< "3.Exit." << endl;
	cout<< endl;
	cout<< "******************************************" <<endl;
	cout<< "Enter your choice:" << endl;
}

void Menu::input(istream& cins) {
	do {
		output(cout);
		cins >> choice;

		switch(choice) {

			case 1:
				check = false;
				
				break;

			case 2:
				cout << "rules" << endl;
				reader.open("Rules.txt");

				if(reader.fail()) {
					cout<< "File failed to open." << endl;
					exit (1);
				}
				do {
					reader.get(read);
					cout << read;

				} while(!reader.eof());
				cout <<endl;
				reader.close();
				check = true;
				
				system("pause");
				break;

			case 3:
				cout << "Goodbye." << endl;
				check = false;

				system("pause");
				exit(0); // added this too terminate the program, without it it jumps out of switch statement then back to main
				break;

			default:
				cout <<"invalid choice. try again." << endl;
				check = true;
				
				break;
		}
	} while(check);
}

void Menu::opening() {

	cout<< "\t \t \t \t \t $$$$$$$\\   $$$$$$\\  $$\\   $$\\ $$$$$$$$\\ $$$$$$$\\" << endl;
	cout<< "\t \t \t \t \t $$  __$$\\ $$  __$$\\ $$ | $$  |$$  _____|$$  __$$\\" << endl;
	cout<< "\t \t \t \t \t $$ |  $$ |$$ /  $$ |$$ |$$  / $$ |      $$ |  $$ |" << endl;
	cout<< "\t \t \t \t \t $$$$$$$  |$$ |  $$ |$$$$$  /  $$$$$\\    $$$$$$$  |" << endl;
	cout<< "\t \t \t \t \t $$  ____/ $$ |  $$ |$$  $$<   $$  __|   $$  __$$<" << endl;
	cout<< "\t \t \t \t \t $$ |      $$ |  $$ |$$ |\\$$\\  $$ |      $$ |  $$ |" << endl;
	cout<< "\t \t \t \t \t $$ |       $$$$$$  |$$ | \\$$\\ $$$$$$$$\\ $$ |  $$ |" << endl;
	cout<< "\t \t \t \t \t \\__|       \\______/ \\__|  \\__|\\________|\\__|  \\__|" << endl;
	cout<<endl;
	cout<<endl;
	cout<< endl;
	cout<< "\t \t \t \t \t \t By: Tho Le and Irving Molina." <<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;

}

