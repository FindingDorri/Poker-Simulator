#ifndef USER_H
#define USER_H

using namespace std;

class user
{
	public:
		user();
		string setName(int max);
		double updatePot(double pot, double bet);
		bool isFold;
		bool isAllin;
		bool outofMoney;
		string name;
		double pot;
	protected:
};
 void updatePot(double bet);

#endif
