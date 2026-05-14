#include <iostream>
#include <math.h>
#include <float.h>
#include "vector.h"
#include "point.h"

vector::vector(const point& A, const point& B) :A(A), B(B)
{

}

double vector::i(){
	return (B.x() - A.x());
}
double vector::j(){
	return (B.y() - A.y());
}
double vector::k(){
	return (B.z() - A.z());
}

bool vector::equally(vector vector)
{
	return bool(abs(vector.i() - i()) < DBL_EPSILON && abs(vector.j() - j()) < DBL_EPSILON && abs(vector.k() - k()) < DBL_EPSILON);
}

vector vector::addition(vector vect)
{
	point A = point(0.0, 0.0, 0.0);
	point B = point(i() + vect.i(), j() + vect.j(), k() + vect.k());
	return vector(A, B);
}

vector vector::subtraction(vector vect)
{
	point A = point(0.0, 0.0, 0.0);
	point B = point(i() - vect.i(), j() - vect.j(), k() - vect.k());
	return vector(A, B);
}

vector vector::multiply(const double a)
{
	point A = point(0.0, 0.0, 0.0);
	point B = point(i() * a, j() * a, k() * a);
	return vector(A, B);
}
