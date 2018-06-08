#include <vector>
#include "die.h"
#include <time.h>

using namespace std;

class SetOfDice
{

public:

	SetOfDice()
	{
		Die d;
		for (int i = 0; i < 5; i++)
		{
			dice.push_back(d);
		}
	}

	~SetOfDice()
	{
	}


	void roll()
	{
		for (unsigned int i = 0; i < dice.size(); i++)
		{
			dice[i].roll();
		}
	}

	int getDie1Value()
	{
		return dice[0].getValue();
	}

	int getDie2Value()
	{
		return dice[1].getValue();
	}

	int getDie3Value()
	{
		return dice[2].getValue();
	}

	int getDie4Value()
	{
		return dice[3].getValue();
	}

	int getDie5Value()
	{
		return dice[4].getValue();
	}

private:

	vector<Die> dice;
};