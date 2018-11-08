#include <iostream>
#include <Windows.h>

int main()
{
	std::cout << " ::: HELLO WORLD ::: " << std::endl;

	auto start = GetTickCount64();


	auto end = GetTickCount64();
	std::cout << " Execution time :: " << end - start << std::endl;

	int _lastPause;
	std::cin >> _lastPause;

	return 0;
}