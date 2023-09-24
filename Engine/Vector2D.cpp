#include "Vector2D.h"
#include <math.h> 

Vector2D::Vector2D(float x, float y)
{
	X = x;
	Y = y;
}
double Vector2D::GetMag()
{
	if (X != 0 || Y != 0)
	{
		return sqrt(pow(X, 2) + pow(Y, 2));
	}
	
	return 0;
}
double Vector2D::GetDir()
{

	if (X != 0 || Y != 0)
	{
		if (Y >= 0)
			return acos(X / GetMag());
		else
			return 2 * 3.14 - acos(X / GetMag());
	}

	return 0;
}
void Vector2D::NormalizeVector()
{
	if(GetMag() > 0 )
	{
		double mag = GetMag();
		X = static_cast<float>(X / mag);
		Y = static_cast<float>(Y / mag);
	}
		
};

