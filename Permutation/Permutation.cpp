#include <iostream>
#include <fstream>
#include <windows.h>

bool IsPermutation(unsigned int a, unsigned int b)
{
	if (a >= b)
	{
		return false;
	}

	unsigned int _a = a;
	unsigned int _b = b;

	char digits[10] = { 0 };

	while (a > 0)
	{
		digits[a % 10]++;
		a = a / 10;
		digits[b % 10]--;
		b = b / 10;
	}

	if (b > 0)
	{
		// b has more digits than a
		return false;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (digits[i] != 0)
			{
				return false;
			}
		}
	}

	std::cout << " " << _a << " , " << _b << std::endl;
	return true;
}

unsigned int CountPermutation(unsigned int N)
{	
	int result = 0;

	for (unsigned int A = 12; A < N; A++)
	{
		for (unsigned int B = A + 1; B < N; B++)
		{
			if (IsPermutation(A, B))
			{
				result++;
			}
		}
	}

	return result;
}

int main()
{
	std::cout << " ::: PERMUTATION ::: " << std::endl;

	auto start = GetTickCount64();

	unsigned int N = 300;
	unsigned int result = CountPermutation(N);

	auto end = GetTickCount64();

	std::cout << " N = " << N << " ; number of permuations :: " << result << std::endl;
	std::cout << " Execution time :: " << end - start << std::endl;	

	/*
	std::fstream file;
	file.open("INPUT.txt", std::ios::in);

	
	if (!file)
	{
		std::cout << "Could not load file" << std::endl;
		return -1;
	}
	else
	{
		file >> N;
	}

	file.close();

	unsigned int result = CountPermutation(N);

	file.open("OUTUT.txt", std::ios::out);
	file << result;
	file.close();
	*/

	int _lastPause;
	std::cin >> _lastPause;

	return 0;
}
