#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MOD = 1e9 + 7;

int count_arrays_tab(int size, int upper_bound, vector<int> &arr)
{
	vector<vector<int>> count_subarrays(size, vector<int>(upper_bound + 2));

	for (int curr = 1; curr <= upper_bound; ++curr)
		if (arr[0] == 0 || arr[0] == curr)
			count_subarrays[0][curr] = 1;

	for (int idx = 1; idx < size; ++idx)
		for (int curr = 1; curr <= upper_bound; ++curr)
			if (arr[idx] == 0 || arr[idx] == curr)
				for (int diff = -1; diff <= 1; ++diff)
					(count_subarrays[idx][curr] += count_subarrays[idx - 1][curr + diff]) %= MOD;

	int total_count = 0;
	for (int curr = 1; curr <= upper_bound; ++curr)
		(total_count += count_subarrays[size - 1][curr]) %= MOD;
	return total_count;
}

int count_subarrays_rec(int idx, int next, int upper_bound, vector<int> &arr, vector<vector<int>> &count_subarrays)
{
	if (idx == -1)
		return 1;
	if (count_subarrays[idx][next] != -1)
		return count_subarrays[idx][next];

	int total_count = 0;
	if (arr[idx] != 0)
	{
		if (abs(arr[idx] - next) > 1)
			total_count = 0;
		else
			total_count = count_subarrays_rec(idx - 1, arr[idx], upper_bound, arr, count_subarrays);
	}
	else
		for (int curr = max(1, next - 1); curr <= min(upper_bound, next + 1); ++curr)
			(total_count += count_subarrays_rec(idx - 1, curr, upper_bound, arr, count_subarrays)) %= MOD;
	return count_subarrays[idx][next] = total_count;
}

int count_arrays_rec(int size, int upper_bound, vector<int> &arr)
{
	vector<vector<int>> count_subarrays(size, vector<int>(upper_bound + 1, -1));

	if (arr[size - 1] != 0)
		return count_subarrays_rec(size - 2, arr[size - 1], upper_bound, arr, count_subarrays);

	int total_count = 0;
	for (int curr = 1; curr <= upper_bound; ++curr)
		(total_count += count_subarrays_rec(size - 2, curr, upper_bound, arr, count_subarrays)) %= MOD;
	return total_count;
}

int count_arrays(int size, int upper_bound, vector<int> &arr)
{
	if (size == 0)
		return 0;

	// return count_arrays_rec(size, upper_bound, arr);
	return count_arrays_tab(size, upper_bound, arr);
}

int main()
{
	int size, upper_bound;
	cin >> size >> upper_bound;

	vector<int> arr(size);
	for (int i = 0; i < size; ++i)
		cin >> arr[i];

	auto start_time = high_resolution_clock::now();

	cout << count_arrays(size, upper_bound, arr) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}