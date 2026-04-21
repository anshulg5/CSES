#include <iostream>
#include <chrono>
#include <vector>
#include <stack>

using namespace std;
using namespace std::chrono;

void iter_mountains(int start, int end, const vector<int> &heights, vector<int> &dp_max_path_len)
{
	stack<int> monotonic_heights;

	for (int idx = start; idx != end; idx += (start < end ? 1 : -1))
	{
		while (!monotonic_heights.empty() && heights[idx] > heights[monotonic_heights.top()])
		{
			dp_max_path_len[idx] = max(dp_max_path_len[idx], 1 + dp_max_path_len[monotonic_heights.top()]);
			monotonic_heights.pop();
		}
		monotonic_heights.push(idx);
	}

	// for (int path_len : dp_max_path_len)
	// 	cout << path_len << ' ';
	// cout << endl;
}

int max_mountains_visited(int size, const vector<int> &heights)
{
	vector<int> dp_max_path_len(size);

	for (int i = 0; i < size; ++i)
	{
		iter_mountains(0, size, heights, dp_max_path_len);
		iter_mountains(size - 1, -1, heights, dp_max_path_len);
	}

	int max_path_len = 0;
	for (int path_len : dp_max_path_len)
		max_path_len = max(max_path_len, path_len);
	return max_path_len + 1;
}

// TODO: Incomplete solution. Optimization needed.
int main()
{
	int numMountains;
	cin >> numMountains;

	vector<int> mountainHeights(numMountains);
	for (int i = 0; i < numMountains; ++i)
		cin >> mountainHeights[i];

	auto start_time = high_resolution_clock::now();

	cout << max_mountains_visited(numMountains, mountainHeights) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}