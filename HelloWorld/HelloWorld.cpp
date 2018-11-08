#include <iostream>
#include <Windows.h>

int main()
{
	auto start = GetTickCount64();


	auto end = GetTickCount64();
	std::cout << " Execution time :: " << end - start << std::endl;

	int _lastPause;
	std::cin >> _lastPause;

	return 0;
}