#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int edit_distance(string s1, string s2)
{
	if (s1.size() == 0 || s2.size() == 0)
		return max(s1.size(), s2.size());

	if (s1.size() < s2.size())
		swap(s1, s2);

	vector<vector<int>> dp_min_edits(2, vector<int>(s2.size() + 1));

	for (int idx2 = 1; idx2 <= s2.size(); ++idx2)
		dp_min_edits[0][idx2] = idx2;

	for (int idx1 = 1; idx1 <= s1.size(); ++idx1)
	{
		int row = idx1 & 1;
		dp_min_edits[row][0] = idx1;
		for (int idx2 = 1; idx2 <= s2.size(); ++idx2)
		{
			dp_min_edits[row][idx2] = min(dp_min_edits[row ^ 1][idx2 - 1] + (s1[idx1 - 1] != s2[idx2 - 1]),
										  min(dp_min_edits[row ^ 1][idx2] + 1,
											  dp_min_edits[row][idx2 - 1] + 1));
		}
	}
	return dp_min_edits[s1.size() & 1][s2.size()];
}

int main()
{
	string s1, s2;
	cin >> s1 >> s2;

	auto start_time = high_resolution_clock::now();

	cout << edit_distance(s1, s2) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}