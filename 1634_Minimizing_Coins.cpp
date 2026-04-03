#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using namespace std::chrono;

const int INF = 1e9;

int minimizing_coins(int total_sum, const vector<int> &coin_values)
{
	vector<int> min_ways(total_sum + 1, INF);
	min_ways[0] = 0;

	for (int sum = 1; sum <= total_sum; ++sum)
	{
		for (int coin_value : coin_values)
		{
			if (sum - coin_value >= 0)
				min_ways[sum] = min(min_ways[sum], min_ways[sum - coin_value] + 1);
		}
	}
	return min_ways[total_sum] == INF ? -1 : min_ways[total_sum];
}

int main()
{

	auto start_time = high_resolution_clock::now();

	int num_coins, total_sum;
	cin >> num_coins >> total_sum;

	vector<int> coin_values(num_coins);
	for (int i = 0; i < num_coins; ++i)
		cin >> coin_values[i];

	cout << minimizing_coins(total_sum, coin_values) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}