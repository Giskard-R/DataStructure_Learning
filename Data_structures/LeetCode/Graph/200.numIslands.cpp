#include <vector>
#include <array>
#include <queue>
#include <stack>

// BFS
class Solution
{
private:
	const std::array<std::array<int, 2>, 4> dir = { { {1,0},{-1,0},{0,1},{0,-1} } };
public:
	int numIslands(std::vector<std::vector<char>>& grid)
	{
		int m = grid.size();
		if (m == 0)
			return 0;
		int n = grid[0].size();
		int cnt = 0;
		std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == '1' && !vis[i][j])
				{
					cnt++;
					std::queue<std::pair<int, int>> q;
					q.push({ i,j });
					vis[i][j] = true;
					while (!q.empty())
					{
						std::pair<int, int> cur = q.front();
						q.pop();
						int x = cur.first;
						int y = cur.second;
						for (auto& d : dir)
						{
							int nx = x + d[0];
							int ny = y + d[1];
							if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1' && !vis[nx][ny])
							{
								vis[nx][ny] = true;
								q.push({ nx,ny });
							}
						}
					}
				}
			}
		}
		return cnt;
	}
};

// DFS
class Solution1
{
private:
	const std::array<std::array<int, 2>, 4> dir = { { {1,0},{-1,0},{0,1},{0,-1} } };
public:
	int numIslands(std::vector<std::vector<char>>& grid)
	{
		int m = grid.size();
		if (m == 0)
			return 0;
		int n = grid[0].size();
		int cnt = 0;
		std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == '1' && !vis[i][j])
				{
					cnt++;
					std::stack<std::pair<int, int>> st;
					st.push({ i,j });
					vis[i][j] = true;
					while (!st.empty())
					{
						std::pair<int, int> cur = st.top();
						st.pop();
						int x = cur.first;
						int y = cur.second;
						for (auto& d : dir)
						{
							int nx = x + d[0];
							int ny = y + d[1];
							if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1' && !vis[nx][ny])
							{
								vis[nx][ny] = true;
								st.push({ nx,ny });
							}
						}
					}
				}
			}
		}
		return cnt;
	}
};