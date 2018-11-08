#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

int t1, t2;
struct Point
{	
	Point(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
	unsigned int x, y;
};

int CheckNextMoveAt(int x , int y, unsigned int prevMinSteps, std::vector<Point>& _tmpNextMoves, unsigned int m, unsigned int n, unsigned int**  jungle, unsigned int** minSteps)
{
	if (x < 0 || y < 0 || x >= m || y >= n)
	{
		return -1;
	}	
	
	if (jungle[x][y] == 0 || jungle[x][y] == 2)
	{
		// can't move, do nothing
		return -1;
	}

	if (jungle[x][y] == 1)
	{
		if (minSteps[x][y] == -1)
		{
			minSteps[x][y] = prevMinSteps + 1;
			_tmpNextMoves.push_back(Point(x, y));
		}
		else
		{
			if (minSteps[x][y] >= prevMinSteps + 1)
			{
				minSteps[x][y] = prevMinSteps + 1;
				_tmpNextMoves.push_back(Point(x, y));
			}
		}
	}

	if (jungle[x][y] == 4)
	{
		t1 = x;
		t2 = y;
		if (minSteps[x][y] == -1)
		{
			minSteps[x][y] = prevMinSteps + 1;
		}
		else
		{
			if (minSteps[x][y] >= prevMinSteps + 1)
			{
				minSteps[x][y] = prevMinSteps + 1;				
			}
		}
	}
}

int FindMinSteps(unsigned int m, unsigned int n, unsigned int **jungle)
{
	int a, b;
	bool isFoundStartingPoint = false;
	for (a = 0; a < m; a++)
	{ 
		for (b = 0; b < n; b++)
		{
			if (jungle[a][b] == 3)
			{
				isFoundStartingPoint = true;
				break;
			}
		}

		if (isFoundStartingPoint)
		{
			break;
		}
	}

	std::cout << " a = " << a << " b = " << b << std::endl;

	// min steps array
	unsigned int ** minSteps;
	minSteps = new unsigned int*[m];
	for (size_t i = 0; i < m; i++)
	{
		minSteps[i] = new unsigned int[n];
		for (size_t j = 0; j < n; j++)
		{
			minSteps[i][j] = -1;
		}
	}

	std::vector<Point> nextMoves;
	nextMoves.push_back(Point(a, b));
	
	while(!nextMoves.empty())
	{
		std::vector<Point> _tmpNextMoves;
		for (auto point : nextMoves)
		{
			unsigned int x = point.x;
			unsigned int y = point.y;
			CheckNextMoveAt(x - 1, y, minSteps[x][y], _tmpNextMoves, m, n, jungle, minSteps);
			CheckNextMoveAt(x + 1, y, minSteps[x][y], _tmpNextMoves, m, n, jungle, minSteps);
			CheckNextMoveAt(x , y - 1, minSteps[x][y], _tmpNextMoves, m, n, jungle, minSteps);
			CheckNextMoveAt(x , y + 1, minSteps[x][y], _tmpNextMoves, m, n, jungle, minSteps);
		}
		std::swap(_tmpNextMoves, nextMoves);
	}

	return minSteps[t1][t2];
}

void ReadInput(std::string path, unsigned int &m, unsigned int &n, unsigned int** &jungle)
{
	std::fstream inp;
	inp.open(path, std::ios::in);
	if (inp.is_open())
	{
		inp >> m >> n;
		jungle = new unsigned int*[m];
		for (size_t i = 0; i < m; i++)
		{
			jungle[i] = new unsigned int[n];
			for (size_t j = 0; j < n; j++)
			{
				inp >> jungle[i][j];
			}
		}		
	}
	else
	{
		std::cout << "Cannot load input file";
	}
}

int main()
{
	std::cout << " ::: PATH TO HONEY ::: " << std::endl;
	auto start = GetTickCount64();
	// input
	std::string _INP_PATH = "INPUT.txt";
	std::string _OUT_PATH = "OUTPUT.txt";

	unsigned int m, n;
	unsigned int **jungle = nullptr;
	unsigned int max_s = 0;
	ReadInput(_INP_PATH, m, n, jungle);
	
	int steps = FindMinSteps(m, n, jungle);

	auto end = GetTickCount64();
	std::cout << " Min steps :: " << steps << std::endl;
	std::cout << " Execution time :: " << end - start << std::endl;

	int _lastPause;
	std::cin >> _lastPause;

	return 0;
}