#include <vector>
#include <queue>
#include <array>

class Solution
{
private:
	const std::array<std::array<int, 2>, 4> dir = { {{1,0},{-1,0},{0,1},{0,-1}} };
public:
	int orangesRotting(std::vector<std::vector<int>>& grid)
	{
		int m = grid.size();
		if (m == 0)
			return 0;
		int n = grid[0].size();
		std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));
		int rottedTime = 0;
		std::queue<std::pair<int, int>> q;
		int freshOrange = 0;

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == 2)
				{
					vis[i][j] = true;
					q.push({ i,j });
				}
				else if (grid[i][j] == 1)
					freshOrange++;
			}
		}
		while (!q.empty() && freshOrange>0)
		{
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				auto e = q.front();
				q.pop();
				int x = e.first;
				int y = e.second;
				for (const auto& d : dir)
				{
					int nx = x + d[0];
					int ny = y + d[1];
					if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1 && !vis[nx][ny])
					{
						vis[nx][ny] = true;
						q.push({ nx,ny });
						freshOrange--;
					}
				}
			}
			rottedTime++;
		}
		if (freshOrange > 0)
			return -1;
		return rottedTime;
	}
};