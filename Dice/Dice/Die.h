#include "TomRandom.h"

class Die
{
public:

	void roll()
	{
		value = randomNumberGenerator.getInt(1, 6);
	}

	int getValue()
	{
		return value;
	}

private:

	int value;
	static TomRandom randomNumberGenerator;
};