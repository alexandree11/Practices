/*
	Name: SortableVector.cpp
	Copyright: 2023
	Author: Aleksandr An
	Date: 03/12/23 18:53
	Description: this program has a class template that is derived from
				SimpleVector class. The main purpose of this program is
				to sort vector object in an ascending order
*/
#include <iostream>
#include "FeetInches.h"
#include "SimpleVector.h"
#include <algorithm>
template <class T>
class SortableVector:public SimpleVector<T> {
	public:
		SortableVector():SimpleVector<T>() {}
		SortableVector(int size):SimpleVector<T>(size) {}
		void sortVector();
		void printBefore();
		void printAfter();
};

// Function to print data before the sort
template <class T>
void SortableVector<T>::printBefore() {
	cout << "The Vector before sorting:\n";
	for(int i = 0; i < this->size(); i++)
		cout << this->operator[](i) << endl;
}

// Function to print data after the sort
template <class T>
void SortableVector<T>::printAfter() {
	cout << "The Vector after sorting:\n";
	for(int i = 0; i < this->size(); i++)
		cout << this->operator[](i) << endl;
}
template <class T>
void SortableVector<T>::sortVector() {
	for(int i = 0; i < this->size(); i++) {
		int minIndex = i;
		for(int j = i + 1; j < this->size(); j++)
			if(this->operator[](j) < this->operator[](minIndex))
				minIndex = j;
		if(minIndex != i)
			swap(this->operator[](i), this->operator[](minIndex));
	}
}

// Function to populate the vector of feet and inches
void fillFeetInches(SortableVector<FeetInches>& feetInchesVector) {
	feetInchesVector[0] = {3, 13};
	feetInchesVector[1] = {8, 4};
	feetInchesVector[2] = {4, 12};
	feetInchesVector[3] = {6, 9};
	feetInchesVector[4] = {6, 2};
	feetInchesVector[5] = {6, 5};
	feetInchesVector[6] = {5, 6};
	feetInchesVector[7] = {5, 1};
}

// Function to test the vector of feet and inches
void testFeetInches(int size) {
	cout << "Testing Vector for FeetInches:\n";
	SortableVector<FeetInches> feetInchesVector(size);
	fillFeetInches(feetInchesVector);
	feetInchesVector.printBefore();
	feetInchesVector.sortVector();
	feetInchesVector.printAfter();
	cout << endl;
}

// Function to populate the vector of integers
void fillIntVector(SortableVector<int>& intVector) {
	intVector[0] = 16;
	intVector[1] = 6;
	intVector[2] = 18;
	intVector[3] = 1;
	intVector[4] = 24;
	intVector[5] = 13;
	intVector[6] = 30;
	intVector[7] = 11;
}

// Function to test the vector of integers
void testIntVector(int size) {
	cout << "Testing Vector of integers:\n";
	SortableVector<int> intVector(size);
	fillIntVector(intVector);
	intVector.printBefore();
	intVector.sortVector();
	intVector.printAfter();
}

// Main test driver
int main(int argc, char** argv) {
	const int SIZE = 8;
	testFeetInches(SIZE);
	testIntVector(SIZE);
	return 0;
}