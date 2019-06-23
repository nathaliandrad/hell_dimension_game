#pragma once
#include <math.h>

class Vector
{
public:
	float x, y;


	Vector();
	Vector(float x,float y);
	
	//returns force or speed, but without direction
	float magnitude(){
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	//rotate vector, keep speed, but change direction
	Vector setAngle(float radians){
		Vector v = *this;//copy current values across

		v.x = cos(radians)*magnitude();
		v.y = sin(radians)*magnitude();

		return v;
	}
};

