#pragma once
#include <cassert>
#include <iostream>

class Assert
{
public:
	//Int
	void AssertCheck(int* Int) {
		assert (Int != nullptr); }
	//Float
	void AssertCheck(float* Float) {
		assert(Float != NULL); }
	//String
	void AssertCheck(std::string* String){
		assert(String != NULL); }
	//Double
	void AssertCheck(double* Double){
		assert(Double != NULL); }
	//Bool = True
	void IsTrue(bool* Bool){
		assert(Bool != false); }
	//Bool = False
	void IsFalse(bool* Bool){
		assert(Bool != true); }

	Assert();
	~Assert();
};

