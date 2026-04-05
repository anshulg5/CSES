#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int minimum_cuts(int side1, int side2)
{
	if (side1 == 0 || side2 == 0)
		return -1;
	else if (side1 == side2)
		return 0;
	if (side1 == 1 || side2 == 1)
		return max(side1, side2) - 1;

	vector<vector<int>> dp_min_cuts(side1 + 1, vector<int>(side2 + 1, 1e9));

	for (int i = 1; i <= side1; ++i)
	{
		for (int j = 1; j <= side2; ++j)
		{
			if (i == j)
				dp_min_cuts[i][j] = 0;
			else
			{
				for (int cut = 1; cut <= i / 2; ++cut)
					dp_min_cuts[i][j] = min(dp_min_cuts[i][j],
											1 + dp_min_cuts[cut][j] + dp_min_cuts[i - cut][j]);
				for (int cut = 1; cut <= j / 2; ++cut)
					dp_min_cuts[i][j] = min(dp_min_cuts[i][j],
											1 + dp_min_cuts[i][cut] + dp_min_cuts[i][j - cut]);
			}
		}
	}
	return dp_min_cuts[side1][side2];
}

int main()
{
	int height, width;
	cin >> height >> width;

	auto start_time = high_resolution_clock::now();

	cout << minimum_cuts(height, width) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}