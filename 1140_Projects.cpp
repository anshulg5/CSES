#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

struct Project
{
	int start;
	int end;
	int value;
};

long max_value(vector<Project> &projects)
{
	auto cmp = [projects](auto p1, auto p2)
	{
		return p1.start < p2.start;
	};
	sort(begin(projects), end(projects), cmp);

	unordered_map<int, long> dp_max_value;
	vector<int> project_starts;

	for (const auto &project : projects)
		if (project_starts.empty() || project_starts.back() != project.start)
			project_starts.push_back(project.start);

	long max_value = 0;
	for (auto itr = projects.rbegin(); itr != projects.rend(); ++itr)
	{
		int start = itr->start;
		if (!dp_max_value.contains(start))
			dp_max_value[start] = max_value;

		long max_next_project_value = 0;
		auto itr_next_project_start = upper_bound(project_starts.begin(), project_starts.end(), itr->end);
		if (itr_next_project_start != project_starts.end())
			max_next_project_value = dp_max_value[*itr_next_project_start];

		dp_max_value[start] = max(dp_max_value[start], itr->value + max_next_project_value);
		max_value = max(max_value, dp_max_value[start]);
	}
	return max_value;
}

int main()
{
	auto start_time = high_resolution_clock::now();

	int num_projects;
	scanf("%d", &num_projects);

	vector<Project> projects;
	projects.reserve(num_projects);
	for (int i = 0; i < num_projects; ++i)
	{
		int start, end, value;
		scanf("%d %d %d", &start, &end, &value);
		projects.emplace_back(start, end, value);
	}

	cout << max_value(projects) << '\n';

	auto end_time = high_resolution_clock::now();

	auto duration_ms = duration_cast<milliseconds>(end_time - start_time);
	cerr << "Execution time: " << duration_ms.count() << " ms" << '\n';

	return 0;
}