#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MOD = 1e9 + 7;

int coin_combinations(int total_sum, const vector<int> &coins)
{
	vector<int> total_ways(total_sum + 1, 0);
	total_ways[0] = 1;

	for (int sum = 1; sum <= total_sum; ++sum)
	{
		for (int coin : coins)
		{
			if (sum - coin >= 0)
			{
				(total_ways[sum] += total_ways[sum - coin]) %= MOD;
			}
		}
	}
	return total_ways[total_sum];
}

int main()
{

	// auto start_time = high_resolution_clock::now();

	int num_coins, total_sum;
	cin >> num_coins >> total_sum;

	vector<int> coins(num_coins);
	for (int i = 0; i < num_coins; ++i)
		cin >> coins[i];

	auto start_time = high_resolution_clock::now();

	cout << coin_combinations(total_sum, coins) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}