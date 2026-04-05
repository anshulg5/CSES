#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int max_pages(int budget, const vector<int> &cost, const vector<int> &pages)
{
	vector<int> total_pages(budget + 1);

	for (int book = 0; book < cost.size(); ++book)
	{
		for (int cur_budget = budget; cur_budget >= cost[book]; --cur_budget)
		{
			total_pages[cur_budget] = max(
				total_pages[cur_budget],
				total_pages[cur_budget - cost[book]] + pages[book]);
		}
	}
	return total_pages[budget];
}

int main()
{
	int num_books, budget;
	cin >> num_books >> budget;

	vector<int> cost(num_books), pages(num_books);
	for (int i = 0; i < num_books; ++i)
		cin >> cost[i];
	for (int i = 0; i < num_books; ++i)
		cin >> pages[i];

	auto start_time = high_resolution_clock::now();

	cout << max_pages(budget, cost, pages) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}