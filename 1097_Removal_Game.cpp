#include <iostream>
#include <chrono>

#include <vector>

using namespace std;
using namespace std::chrono;

long get_sum(int l, int r, const vector<long> &prefix_sum)
{
	return prefix_sum[r + 1] - prefix_sum[l];
}

long max_optimal_score(const vector<int> &nums)
{
	int total_nums = nums.size();
	vector<long> prefix_sum(total_nums + 1);
	for (int i = 0; i < total_nums; ++i)
		prefix_sum[i + 1] += prefix_sum[i] + nums[i];

	vector<long> dp_max_score(total_nums, -1e18);

	for (int l = total_nums - 1; l >= 0; --l)
	{
		dp_max_score[l] = nums[l];
		for (int r = l + 1; r < total_nums; ++r)
		{
			dp_max_score[r] = max(nums[l] + get_sum(l + 1, r, prefix_sum) - dp_max_score[r],
								  nums[r] + get_sum(l, r - 1, prefix_sum) - dp_max_score[r - 1]);
		}
	}
	return dp_max_score[total_nums - 1];
}

int main()
{
	int total_nums;
	cin >> total_nums;

	vector<int> nums(total_nums);
	for (int i = 0; i < total_nums; ++i)
		cin >> nums[i];

	auto start_time = high_resolution_clock::now();

	cout << max_optimal_score(nums) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}