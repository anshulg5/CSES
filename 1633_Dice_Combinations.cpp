#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MOD = 1e9 + 7;

int dice_combinations(int n)
{
	vector<int> total_ways(n + 1);
	total_ways[0] = 1;

	for (int sum = 1; sum <= n; ++sum)
	{
		for (int last_sum = max(0, sum - 6); last_sum < sum; ++last_sum)
			total_ways[sum] = (total_ways[sum] + total_ways[last_sum]) % MOD;
	}

	return total_ways[n];
}

int main()
{

	auto start_time = high_resolution_clock::now();

	int n;
	cin >> n;

	cout << dice_combinations(n) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}