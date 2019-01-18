#include "problems.h"

// Given an one dimensional array of integers.
// Find the subarray containing at least k elements which has the largest sum.
// https://www.geeksforgeeks.org/largest-sum-subarray-least-k-numbers/
// https://en.wikipedia.org/wiki/Maximum_subarray_problem

#if LARGEST_SUM_OF_SUBARRAY

#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

void SolveProblem(unsigned int N, unsigned int K, unsigned int* numbers, unsigned int &result)
{
	
}

void ReadInput(std::string path, unsigned int &N, unsigned int &K, unsigned int* &numbers)
{
	std::fstream inp;
	inp.open(path, std::ios::in);
	if (inp.is_open())
	{
		inp >> N;
		inp >> K;
		numbers = new unsigned int[N];
		for (size_t i = 0; i < N; i++)
		{			
			inp >> numbers[i];
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
	std::cout << " ::: LARGEST SUM OF SUBARRAY ::: " << std::endl;
	
	int numberTestCases = 1;

	for (int i = 1; i <= numberTestCases; i++)
	{
		auto start = GetTickCount64();
		
		// input
		std::string _INP_PATH = "INP.txt";
		std::string _OUT_PATH = "OUT.txt";
		std::string testCasePath = "TestCases";
		testCasePath += "/" + std::to_string(i) + "/";

		unsigned int N, K;
		unsigned int *numbers = nullptr;
		
		ReadInput(testCasePath + _INP_PATH, N, K, numbers);

		unsigned int result;
		SolveProblem(N, K, numbers, result);

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




// https://stackoverflow.com/questions/7861387/maximum-contiguous-subsequence-sum-of-at-least-length-l

/*
int A[N];
int L;

let's consider the case where L = 0. In that case, we want to find the maximum-sum subarray of the original sequence. This can be solved by Kadane's algorithm, a clever dynamic programming solution that works as follows.The idea is to keep track of the weight of the maximum - weight subarray ending just before and just after each position in the array.Whichever of these arrays has the largest sum is the subarray with the maximum total sum.Let the original array be A and let the array of maximum sums ending at position k be array M.Then Kadane's algorithm works like this:

Set M(0) = 0. Any subarray ending just before the first array entry can't have anything in it, so it has sum zero.
For each array index k, in order, set M(k + 1) = max(0, M(k) + A(k)).The idea here is that the best subarray ending just before this position is either formed by extending the best array from the previous position by a single element, or by discarding that array entirely and just picking the empty subarray before this position.
Once you've filled in this table M, you can just scan it to find the maximum value overall, which gives you the weight of the maximum-weight subarray.

But how do we adapt this to the case where L ? 0 ? Fortunately, this isn't too bad. Look at the recurrence for Kadane's algorithm.The idea is that at each point we can either extend the array by one step, or we can reset back to the empty array.But if we have a lower bound on the size of our subarray, we can think of this differently : the maximum - weight subarray of length at least L ending just before position k + 1 is formed either by extending the best array of length at least L that ends just before position k by one element, or by discarding that array and taking the L element subarray that ends right before position k.This gives us a new version of Kadane's algorithm that looks like this:

Set M(L) equal to the sum of the first L elements of the array.
For each array index k = L, in order, set M(k + 1) to the maximum of M(k) + A(k) (the value we get by extending the array) and the sum of the L elements just before position k + 1 (the value we get by just taking the last k elements).
If we run this, we will fill in table M values from L to the length of the array.The maximum value in that range is then the maximum sum subarray value for subarrays of length at least L.

But this doesn't run in linear time! In particular, it runs in O(nL), since each iteration of the computation has to look at the previous L elements of the array. However, by doing some extra pre computation, we can drop this to O(n). The idea is that we can build up a table containing the sums of the L element before each array index in O(n) time as follows. First, sum up the first L elements of the array and store that as S(L). This is the sum of the L elements just before position L. Now, if we want to get the sum of the L elements just before index L + 1, wr can do s by summing up the first L elements of the array, adding in the next array element, then subtracting out the very first array element. This can be done in O(1) time by computing S(L + 1) = S(L) + A(L) - A(0). We can then use a similar trick to compute S(L + 2) = S(L + 1) + A(L + 1) - A(1). More generally, we can fill in this table of partial sums in O(n) time using the recurrence

S(L) = A(0) + A(1) + ... + A(L - 1).
S(L + k + 1) = S(L + k) + A(L + k) - A(k).
This runs in O(n) time.If we have this table precomputed, we can then find the maximum - weight subarray of length at least L by using this recurrence from above :

M(L) = S(L)
M(L + k + 1) = max(M(L + k) + A(L + k), S(L + k))
We can then just scan across the M array to find the maximum value.This whole process runs in O(n) time : we need O(n) time to compute the S array, O(n) time to compute M array, and O(L) = O(n) time to find the maximum value.It also takes O(L) space, since we need to store the M and S arrays.

But we can do better than this by reducing the memory usage to O(1)!The trick is to notice that at each point we don't need the entire M and S arrays; just the last term. We can therefore just store the last value of M and S, which takes only O(1) memory. At each point, we will also keep track of the maximum value we've seen in the M array, so we don't need to hold the M array after we've filled it in.This then gives the following O(n) - time, O(1) - space algorithm for solving the problem :

Set S to the sum of the first L array elements.
Set M = S.
Set Best = M
For k = L + 1 up to n, the length of the array :
Set S = S + A(k) - A(k - L)
Set M = max(M + A(k), S)
Set Best = max(Best, M)
Output Best

http://keithschwarz.com/interesting/code/?dir=generalized-kadane

*/