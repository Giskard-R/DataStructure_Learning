#include <vector>
#include <queue>

class Solution
{
public:
	bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		std::vector<std::vector<int>> adj(numCourses);
		std::vector<int> in(numCourses, 0);
		std::queue<int> q;
		int cnt = 0;

		for (const auto& e : prerequisites)
		{
			int a = e[0];
			int b = e[1];
			adj[b].emplace_back(a);
			in[a]++;
		}

		for (int i = 0; i < numCourses; i++)
		{
			if (in[i] == 0)
			{
				q.push(i);
			}
		}

		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			cnt++;

			for (int v : adj[u])
			{
				in[v]--;
				if (in[v] == 0)
				{
					q.push(v);
				}
			}
		}
		return cnt == numCourses;
	}
};