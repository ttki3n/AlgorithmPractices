#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

struct Point
{	
	Point(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
	unsigned int x, y;
};

int CheckNextMoveAt(int x, int y, unsigned int prevMinSteps, std::queue<Point>& _tmpNextMoves, unsigned int m, unsigned int n, unsigned int**  jungle, unsigned int** minSteps, Point& honey)
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
		jungle[x][y] = 10;
		if (minSteps[x][y] == -1)
		{
			minSteps[x][y] = prevMinSteps + 1;
			_tmpNextMoves.emplace(Point(x, y));
		}
		else
		{
			if (minSteps[x][y] > prevMinSteps + 1)
			{
				minSteps[x][y] = prevMinSteps + 1;
				_tmpNextMoves.emplace(Point(x, y));
			}			
		}
	}

	if (jungle[x][y] == 4)
	{
		honey.x = x;
		honey.y = y;
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

	// min steps array : store the min steps to reach that point	

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

	std::queue<Point> nextMoves;
	nextMoves.emplace(Point(a, b));
	Point honey(-1, -1);

	while(!nextMoves.empty())
	{
		Point point = nextMoves.front();
		nextMoves.pop();	
		
		unsigned int x = point.x;
		unsigned int y = point.y;
		CheckNextMoveAt(x - 1, y, minSteps[x][y], nextMoves, m, n, jungle, minSteps, honey);
		CheckNextMoveAt(x + 1, y, minSteps[x][y], nextMoves, m, n, jungle, minSteps, honey);
		CheckNextMoveAt(x , y - 1, minSteps[x][y], nextMoves, m, n, jungle, minSteps, honey);
		CheckNextMoveAt(x , y + 1, minSteps[x][y], nextMoves, m, n, jungle, minSteps, honey);
		
		if (honey.x != -1)
		{
			return minSteps[honey.x][honey.y];
		}
	}
	
	return -1;
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
	std::cout << " ::: PATH TO HONEY ::: " << std::endl;
	int numberTestCases = 10;

	for (int i = 1; i <= numberTestCases; i++)
	{
		auto start = GetTickCount64();
		// input
		std::string _INP_PATH = "INP.txt";
		std::string _OUT_PATH = "OUT_1.txt";
		std::string testCasePath = "TestCases";
		testCasePath += "/" + std::to_string(i) + "/";

		unsigned int m, n;
		unsigned int **jungle = nullptr;
		unsigned int max_s = 0;
		ReadInput(testCasePath + _INP_PATH, m, n, jungle);

		int steps = FindMinSteps(m, n, jungle);

		auto end = GetTickCount64();
		std::string output = std::to_string(end - start) + " ms" + "\n" + std::to_string(steps);
		WriteOutput(testCasePath + _OUT_PATH, output);
		std::cout << " Min steps :: " << steps << std::endl;
		std::cout << " Execution time :: " << end - start << std::endl;

	}
	int _lastPause;
	std::cin >> _lastPause;

	return 0;
}