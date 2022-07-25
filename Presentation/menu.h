#include <fstream>

#ifndef MENU_H
#define MENU_H

using namespace std;

class Menu
{

	private:
		int choice;
		char read;
		bool check;
		
		ifstream reader;
	public:

		Menu();
		void output(ostream& couts);
		void input(istream& cins);
		void opening();
};


#endif
