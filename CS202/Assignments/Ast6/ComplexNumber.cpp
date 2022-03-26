/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_6
Description: This file contains the implenettaion for the complex number
class which has a real and imaginary part. There are various 
mathematical operations that are overloaded to work with real and
imaginary numbers.
Input: File name of the map to read and use
Output: Steps of the map to reach the treasure
*/
#include "ComplexNumber.h"
#include <cmath>

//----------------- Operator overload implementations -----------------
//TODO: Implement ComplexNumber operator overloads

/**/
ComplexNumber operator + (ComplexNumber left, ComplexNumber right){
	//Create a resulting ComplexNumber and assign the correct
	//answer to it. You can change 
	//this to be one line if you know how
	ComplexNumber result;
	//adding the real numbers
	result.real = left.real + right.real;
	//adding the imaginary numbers
	result.imaginary = left.imaginary + right.imaginary;

	return result;
}

/**/
ComplexNumber operator * (ComplexNumber left, ComplexNumber right){
	ComplexNumber result;
	double firsts = left.real * right.real;
	double outers = left.real * right.imaginary;
	double inners = left.imaginary * right.real;
	double lasts = left.imaginary * right.imaginary;

	result.real = firsts + (lasts*-1);
	result.imaginary = outers + inners;

	return result;
}

/**/
ComplexNumber operator * (double scalar, ComplexNumber right){
	//multiply the real and imaginary numbers by the scalar
	ComplexNumber result;
	result.real = right.real * scalar;
	result.imaginary = right.imaginary * scalar;
	return result;
}

/**/
ostream& operator << (ostream& out, const ComplexNumber& cn){
	//Use the ComplexNumber toString function to convert to
	//a string an print
	//then returns the stream
	out << "< " << cn.real << ", " << cn.imaginary << " >\n";
	return out;
}

istream& operator >> (istream& in, ComplexNumber& cn){
	//Reads the real number then the imaginary part from the stream
	//into the ComplexNumber
	in >> cn.real >> cn.imaginary;
	return in;
}

//----------------- Helper function implementations -----------------

//Returns the magnitude of this ComplexNumber, treating it like a vector
double ComplexNumber::magnitude(){
	return sqrt(real * real + imaginary * imaginary);
}

//Normalizes the contents of the vector so that the magnitude is 1
void ComplexNumber::normalize(){
	double m = this->magnitude(); //Get the magnitude of this vector
	this->imaginary /= m;
	this->real /= m;
}

//Returns the complex number in a string of the form:
//<real, imaginary>
string ComplexNumber::toString() const{
	return "<" + to_string(real) + ", " + to_string(imaginary) + ">";
}

//Gets the angle in degrees of the rotation (just for printing)
double ComplexNumber::getDegrees() const{
	//Check for asymptotes before doing arctan
	if (real == 0.0)
		return imaginary < 0.0 ? 270 : 90;

	double refAngle = atan(imaginary / real) * 180.0 / PI;

	//Figure out the quadrant
	if (imaginary < 0.0) //Negative vertical component
	{
		if (real < 0.0) //Quadrant III
			return 180 + refAngle;
		//Quadrant IV
		return 360 + refAngle;
	}
	//Non-negative vertical component
	if (real < 0.0) //Quadrant II
		return 180 + refAngle;
	//Quadrant I
	return refAngle;
}
