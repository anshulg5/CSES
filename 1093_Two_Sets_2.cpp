#include <iostream>
#include <chrono>

#include <vector>

using namespace std;
using namespace std::chrono;

const int MOD = 1e9 + 7;

int count_equal_sum_sets(int num)
{
	if (num <= 2)
		return 0;

	int target_sum = num * (num + 1) >> 1;
	if (target_sum & 1)
		return 0;
	target_sum >>= 1;

	vector<int> dp_count_sets(target_sum + 1);
	dp_count_sets[0] = 1;

	for (int i = 1; i < num; ++i)
	{
		for (int sum = target_sum; sum >= i; --sum)
			(dp_count_sets[sum] += dp_count_sets[sum - i]) %= MOD;
	}

	return dp_count_sets[target_sum];
}

int main()
{
	int num;
	cin >> num;

	auto start_time = high_resolution_clock::now();

	cout << count_equal_sum_sets(num) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}