#include <iostream>
#include <chrono>

#include <vector>
#include <unordered_set>

using namespace std;
using namespace std::chrono;

vector<int> find_all_sums(const vector<int> &coins)
{
	unordered_set<int> prev_sums, curr_sums;
	prev_sums.insert(0);

	for (int coin : coins)
	{
		curr_sums.insert(prev_sums.begin(), prev_sums.end());
		for (int prev_sum : prev_sums)
			curr_sums.insert(prev_sum + coin);
		prev_sums.clear();
		swap(prev_sums, curr_sums);
	}
	prev_sums.erase(0);
	return vector<int>(prev_sums.begin(), prev_sums.end());
}

int main()
{
	int numCoins;
	cin >> numCoins;

	vector<int> coins(numCoins);
	for (int i = 0; i < numCoins; ++i)
		cin >> coins[i];

	auto start_time = high_resolution_clock::now();

	vector<int> all_sums = find_all_sums(coins);
	sort(all_sums.begin(), all_sums.end());

	cout << all_sums.size() << '\n';
	for (int sum : all_sums)
		cout << sum << ' ';
	cout << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}