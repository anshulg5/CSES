#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MOD = 1e9 + 7;

const char BLOCK = '*';

int count_paths(int sz, const vector<string> &grid)
{
	if (sz <= 0 || grid[0][0] == BLOCK || grid[sz - 1][sz - 1] == BLOCK)
		return 0;

	vector<int> dp_count_paths(sz);
	dp_count_paths[0] = 1;

	for (int row = 0; row < sz; ++row)
	{
		for (int col = 0; col < sz; ++col)
		{
			if (grid[row][col] == BLOCK)
				dp_count_paths[col] = 0;
			else if (col > 0 && grid[row][col - 1] != BLOCK)
				(dp_count_paths[col] += dp_count_paths[col - 1]) %= MOD;
		}
	}
	return dp_count_paths[sz - 1];
}

int main()
{

	int size;
	cin >> size;

	vector<string> grid(size);
	for (int i = 0; i < size; ++i)
		cin >> grid[i];

	auto start_time = high_resolution_clock::now();

	cout << count_paths(size, grid) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}