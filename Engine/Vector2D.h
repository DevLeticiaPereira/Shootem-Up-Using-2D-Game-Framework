#pragma once

class Vector2D
{
public:
	Vector2D(float x = 0, float y = 0);
	
	//addition
	inline Vector2D operator+(const Vector2D& v2) const {

		return Vector2D(X + v2.X, Y + v2.Y);
	}

	// subtraction
	inline Vector2D operator-(const Vector2D& v2) const {
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	// scalar * Vector operation 
	inline Vector2D operator*(const float scalar) const {
		return Vector2D(X*scalar, Y*scalar);
	}
	 
	// scalar / Vector operation 
	inline Vector2D operator/(const float scalar) const {
		return Vector2D(X / scalar, Y / scalar);
	}

	//dotProduct
	inline float operator* (Vector2D const& v2)
	{
		return X * v2.X + Y * v2.Y;
	}

	inline bool operator<(const Vector2D& v2) const
	{
		return (X * X + Y * Y) < (v2.X * v2.X + v2.Y * v2.Y);
	}

	inline bool operator==(const Vector2D& v2) const
	{
		if (X == v2.X && Y == v2.Y)
		{
			return true;
		}
		
		return false;
	}

	double GetMag();
	double GetDir();
	void NormalizeVector();

	float X{};
	float Y{};

private:

	float dir{};

};

