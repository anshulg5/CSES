#include <iostream>
#include <chrono>

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using namespace std::chrono;

const int INF = 1e9;

int remove_digits(int num)
{
	vector<int> min_steps(num + 1, INF);
	min_steps[0] = 0;

	for (int i = 1; i <= num; ++i)
	{
		int cur_num = i;
		while (cur_num > 0)
		{
			int digit = cur_num % 10;
			min_steps[i] = min(min_steps[i], min_steps[i - digit] + 1);
			cur_num /= 10;
		}
	}
	return min_steps[num];
}

int main()
{

	// auto start_time = high_resolution_clock::now();

	int num;
	cin >> num;

	auto start_time = high_resolution_clock::now();

	cout << remove_digits(num) << endl;

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << endl;

	return 0;
}