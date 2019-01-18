#include "problems.h"

// Given a list of N coins, their values(V1, V2, …, VN), and the total sum S.
// Find the minimum number of coins the sum of which is S(we can use as many coins of one type as we want), 
// or report that it’s not possible to select coins in such a way that they sum up to S.

#if KNAPSACK_SUM_OF_COINS

#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

void SolveProblem(unsigned int N, unsigned int S, unsigned int values[], unsigned int &result)
{
	unsigned int* minCoinsArray = new unsigned int[S + 1];
	minCoinsArray[0] = 0;
	for (int i = 1; i <= S; i++)
	{
		unsigned int minCoins = S + 1;
		for (int j = 0; j < N; j++)
		{
			if (i < values[j])
			{
				continue;
			}
			unsigned int tmpMinCoins = minCoinsArray[i - values[j]] +1;
			if (tmpMinCoins < minCoins)
			{
				minCoins = tmpMinCoins;
			}			
		}

		minCoinsArray[i] = minCoins;
	}
	
	result = minCoinsArray[S];
	if (result == S + 1)
	{
		// couldn't find solution
		result = 0;
	}
}

void ReadInput(std::string path, unsigned int &totalCoins, unsigned int &sum, unsigned int* &coinsValue)
{
	std::fstream inp;
	inp.open(path, std::ios::in);
	if (inp.is_open())
	{
		inp >> totalCoins;
		inp >> sum;
		coinsValue = new unsigned int[totalCoins];
		for (size_t i = 0; i < totalCoins; i++)
		{			
			inp >> coinsValue[i];			
		}
	}
	else
	{
		std::cout << "Cannot load input file";
	}
}

void WriteOutput(std::string path, std::string s)
{
	std::fstream out;
	out.open(path, std::ios::out);
	if (out.is_open())
	{
		out << s << "\n";
	}
	else
		std::cout << "Cannot write output" << std::endl;

	out.close();
}

int main()
{
	std::cout << " ::: KNAPSACK SUM OF COINS ::: " << std::endl;
	
	int numberTestCases = 1;

	for (int i = 1; i <= numberTestCases; i++)
	{
		auto start = GetTickCount64();
		
		// input
		std::string _INP_PATH = "INP.txt";
		std::string _OUT_PATH = "OUT_1.txt";
		std::string testCasePath = "TestCases";
		testCasePath += "/" + std::to_string(i) + "/";

		unsigned int N, S;
		unsigned int *values = nullptr;
		
		ReadInput(testCasePath + _INP_PATH, N, S, values);

		unsigned int result;
		SolveProblem(N, S, values, result);

		auto end = GetTickCount64();		
		
		std::string executedTime = " ms = " + std::to_string(end - start);		

		std::cout << " Min coins :: " << result << std::endl;
		std::cout << " Execution time :: " << executedTime << std::endl;

		std::fstream out;
		out.open(testCasePath + _OUT_PATH, std::ios::out);
		if (out.is_open())
		{
			out << result << std::endl;
			out << executedTime;
		}
		else
		{
			std::cout << "Cannot write output" << std::endl;
		}

		out.close();
	}

	char _lastPause;
	std::cin >> _lastPause;

	return 0;
}

#endif