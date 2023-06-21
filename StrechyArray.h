#pragma once
#include<iostream>
using namespace std;

template <class A>
class StrecthyArray
{
	A* arr;
	int siz;
	int ind;
	
public:
	StrecthyArray(string word)
	{
		siz = 790000; arr = new A[siz]; ind = 0; 
	}
	void insertelement(A element)
	{
        
		
		
			arr[ind] = element;
			ind++;
		
	}
	void display()
	{
		
		for (int i = 0; i < ind+1; i++)
		{
			cout<<"\"" << arr[i] << "\""; (i + 1 == siz) ? cout << "" : cout << " , ";
			
		}
	}
	int returnsize()
	{
		int s = ind+1 ;
		return s;
	}
	A* returnArr()
	{
		return arr;
	}
};