// proj3
// 
// Author: Marc Maromonte

#include "pch.h"
#include <iostream>
#include <array>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

int inversions = 0;

void Merge( int B[], int p, int C[], int q, int A[] )
{
	int i = 0, j = 0, k = 0;

	while (i < p && j < q)
	{
		if (B[i] <= C[j])
		{
			A[k] = B[i];
			i++;
		}
		else
		{
			A[k] = C[j];
			j++;
			inversions += p - i;
		}
		k++;
	}

	if (i == p)
	{
		while (j < q)
		{
			A[k] = C[j];
			k++;
			j++;
		}
	}
	else
	{
		while (i < p)
		{
			A[k] = B[i];
			k++;
			i++;

		}

	}
}

void CountInversion( int A[], int size )
{

	if (size > 1)
	{
		int * B = new int[floor((size / 2))];
		int * C = new int[ceil((size / 2))];

		for (int i = 0; i < floor((size / 2)); i++)
		{
			B[i] = A[i];
		}

		int aIndex = floor(size / 2);

		for (int j = 0; j < ceil((size/2)) || aIndex < size; j++)
		{
			C[j] = A[aIndex];
			aIndex++;
		}

		CountInversion(B, floor((size / 2)));

		if (size % 2 == 0)
		{
			CountInversion(C, ceil((size / 2)));
			Merge(B, floor((size / 2)), C, ceil((size / 2)), A);
		}
		else
		{
			CountInversion(C, ceil((size / 2))+1);
			Merge(B, floor((size / 2)), C, ceil((size / 2))+1, A);
		}
	}
}

int main()
{
	// Opens the input.txt file
	//
	ifstream inFile;
	inFile.open("input.txt");

	// If unable to open file exit
	//
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1);
	}

	// Gets number of test cases
	//
	string line = "";
	int n = 0;

	getline(inFile, line);
	n = stoi(line);

	// Performs inversion count for each test case
	//
	while (n != 0)
	{
		string num;
		queue<string> numQ;
		line = "";
		getline(inFile, line);

		for ( int i = 0; i < line.length(); i++ )
		{	
			if (line.at(i) != ' ')
			{
				num += line.at(i);
			}
			else
			{
				numQ.push(num);
				num = "";
			}

			if (i + 1 == line.length())
			{
				num = line.at(i);
				numQ.push(num);
				num = "";
			}
		}

		// Creates array for sequence of numbers
		//
		int * A = new int[numQ.size()];
		int count = 0;

		while( !numQ.empty() )
		{
			A[count] = stoi(numQ.front());
			numQ.pop();
			count++;
		}

		CountInversion(A, count);

		cout << "The sequence has " << inversions << " inversions.\n";

		inversions = 0;
		n--;
	}	

	return 0;
}

	

