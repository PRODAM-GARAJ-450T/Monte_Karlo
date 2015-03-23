#include "grn.h"
#include "stdafx.h"
//public
grn::grn()
{
}

grn::~grn()
{
}

float grn::generate()
{
	float rNumber = 0.0;
	int midSquare = random(), 
		midMultipl = MMS();

	int end;
		end = clockInThisSecond();
	for (int i = 0; i < end ; i++)
	{
		midSquare = MMS(midMultipl);
		midMultipl = MMM(midSquare);
	}

	rNumber = midMultipl;
	rNumber /= 10000;								

	return rNumber;
}

float grn::genInRange(int from, int to)
{
	return (float)(from + generate() * (to - from));
}

int grn::random(int n1, int n2)
{
	int i = 0; 		
	i = n1 + rand() * (n2 - n1);
	
	return i;
}

int grn::MMM(int n) // set dddd, dddd*cccc = ddmmmmdd, mmmm is middle of multiplication 
{
	int fNumber,//first number dddd
		sNumber,//second number cccc
		midMultipl = 0; //mid of multiplication
	
	fNumber = n | setNumber();	//dddd
	sNumber = random();			//cccc
	int end;
		end = clockInThisSecond();
	for (int i = 0; i < 20; i++)// for mutcher range
	{
		midMultipl = midExtract(fNumber * sNumber);
		fNumber = midMultipl;
		if (midMultipl == 0)
		{
			fNumber = setNumber();
			i--;
		}

	}

	return midMultipl;
}

int grn::MMS(int n) // set dddd, sqr(dddd) = ddmmmmdd, mmmm is middle of square
{
	int fNumber,//first number dddd
		midSquare = 0; //mid of square

	fNumber = n == 0 ? setNumber() : n;	//dddd
	int end;
		end = clockInThisSecond();
	for (int i = 0; i < end; i++)
	{
		midSquare = midExtract(fNumber*fNumber);
		fNumber = midSquare == 0 ? midExtract(random()) : midSquare; 
	}

	return midSquare;
}						 

//private ------------------------------------------------

int grn::setNumber()
{
	return 	clockInThisSecond() * 10 + clockInThisSecond();
}

int grn::midExtract(unsigned long int n)
{
	unsigned long int c = n,
					  divider = 10;
	int	middle = 0,
		count = 0;

	do
	{
		c /= 10;
		count++;
	} while (c > 0);


	if ((((count - 4) / 2) - 1) < 0)
		count = (((count - 4) / 2) - 1) * -1;
	else
		count = ((count - 4) / 2) - 1;

	for (int i = 0; i < count; i++)
	{
		divider *= 10;
	}
	middle = (n / divider) % 10000;

	return middle;
}