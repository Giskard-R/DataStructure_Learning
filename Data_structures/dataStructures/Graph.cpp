#if 0 // Matrix Graph

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class MGraph
{
private:
	int vertexNum;
	int edgeNum;
	std::vector<std::vector<int>> arc;
	static constexpr int INF = 0x3f3f3f3f;

	struct Edge
	{
		int u, v, w;

		Edge(int u_, int v_, int w_) :u(u_), v(v_), w(w_) {}

		bool operator<(const Edge& other) const
		{
			return w < other.w;
		}
	};

	std::vector<int> parent;

	// 路径压缩, 略过中间结点, 直接指向根结点
	int Find(int x)
	{
		if (parent[x] != x)
			parent[x] = Find(parent[x]);
		return parent[x];
	}

	void DfsPrivate(int v, std::vector<bool>& vis)
	{
		std::cout << v << " ";
		vis[v] = true;
		// 遍历所有顶点, 寻找v的邻接点
		for (int i = 0; i < vertexNum; i++)
		{
			if (arc[v][i] != INF && !vis[i])
			{
				DfsPrivate(i, vis);
			}
		}
	}

	bool TopoSortHelper(std::vector<int>& topoSeq)
	{
		topoSeq.clear();
		std::vector<int> in(vertexNum, 0);
		std::queue<int> q;
		// 统计所有顶点的入度
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (arc[i][j] != INF && arc[i][j] != 0)
					in[j]++;
			}
		}
		// 将入度为0的顶点入队
		for (int i = 0; i < vertexNum; i++)
		{
			if (in[i] == 0)
				q.push(i);
		}
		// 删去u->v的边
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			topoSeq.emplace_back(u);
			for (int v = 0; v < vertexNum; v++)
			{
				if (arc[u][v] != INF && arc[u][v] != 0)
				{
					in[v]--;
					if (in[v] == 0)
						q.push(v);
				}
			}
		}
		// 检查是否存在环
		if (topoSeq.size() != vertexNum)
		{
			return false;
		}
		return true;
	}

public:
	MGraph(int n, int e)
		:vertexNum(n), edgeNum(e)
	{
		arc.assign(n, std::vector<int>(n, INF));
		for (int i = 0; i < n; i++)
		{
			arc[i][i] = 0;
		}
	}

	void AddUDEdge(int u, int v, int w = 1)
	{
		arc[u][v] = w;
		arc[v][u] = w;
	}

	void AddDEdge(int u, int v, int w = 1)
	{
		arc[u][v] = w;
	}

	void Print()
	{
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (arc[i][j] == INF)
					std::cout << "∞ ";
				else
					std::cout << arc[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Prim()
	{
		std::vector<int> low(vertexNum, INF); // 记录每个点到生成树集合的最短边权
		std::vector<bool> vis(vertexNum, false); // 标记点是否已经加入最小生成树集合
		low[0] = 0; // 初始化起点
		int sum = 0;
		for (int i = 0; i < vertexNum; i++)
		{
			int u = -1;
			int minW = INF;
			// 寻找权值边最小的点
			for (int j = 0; j < vertexNum; j++)
			{
				if (!vis[j] && low[j] < minW)
				{
					minW = low[j];
					u = j;
				}
			}
			if (u == -1)
			{
				std::cout << "图不连通, 无最小生成树\n";
				return;
			}
			vis[u] = true;
			sum += minW;
			// 更新新加点后的最小边权值
			for (int v = 0; v < vertexNum; v++)
			{
				if (!vis[v] && arc[u][v] != INF && arc[u][v] < low[v])
				{
					low[v] = arc[u][v];
				}
			}
		}
		std::cout << "Prim最小生成树权值和: " << sum << std::endl;
	}

	void Kruskal()
	{
		std::vector<Edge> edges;
		// 初始化邻接矩阵
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = i + 1; j < vertexNum; j++)
			{
				if (arc[i][j] != INF)
				{
					edges.emplace_back(i, j, arc[i][j]);
				}
			}
		}
		// 按权值升序排列
		std::sort(edges.begin(), edges.end());
		// 初始化parent[], sum, cnt
		parent.resize(vertexNum);
		for (int i = 0; i < vertexNum; i++)
		{
			parent[i] = i;
		}
		int sum = 0;
		int cnt = 0;
		// 循环依次取边
		for (auto& e : edges)
		{
			int fu = Find(e.u);
			int fv = Find(e.v);
			if (fu != fv)
			{
				parent[fv] = fu;
				sum += e.w;
				cnt++;
				if (cnt == vertexNum - 1)
					break;
			}
		}
		// 检查所用结点数量
		if (cnt != vertexNum - 1)
		{
			std::cout << "图不连通, 无最小生成树\n";
			return;
		}
		std::cout << "Kruskal最小生成树权值和: " << sum << std::endl;
	}

	void Dijkstra(int start)
	{
		std::vector<int> dist(vertexNum, INF); // 起点到i的当前最短距离
		std::vector<bool> vis(vertexNum, false);
		// 起点到自身的距离为0
		dist[start] = 0;
		// 每个循环确定一个点的最短距离
		for (int i = 0; i < vertexNum; i++)
		{
			int u = -1;
			int minD = INF;
			// 找到未确定且dist最小的点u
			for (int j = 0; j < vertexNum; j++)
			{
				if (!vis[j] && dist[j] < minD)
				{
					minD = dist[j];
					u = j;
				}
			}
			if (u == -1)
				break;
			vis[u] = true;

			for (int v = 0; v < vertexNum; v++)
			{
				if (!vis[v] && arc[u][v] != INF && dist[v] > dist[u] + arc[u][v])
				{
					dist[v] = dist[u] + arc[u][v];
				}
			}
		}
		std::cout << "Dijkstra起点: " << start << std::endl;
		for (int i = 0; i < vertexNum; i++)
		{
			if (dist[i] == INF)
			{
				std::cout << i << "不可达";
			}
			else
			{
				std::cout << i << " : " << dist[i] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Floyd()
	{
		std::vector<std::vector<int>> dist(vertexNum, std::vector<int>(vertexNum));
		std::vector<std::vector<int>> path(vertexNum, std::vector<int>(vertexNum));
		// 初始化距离矩阵dist和前驱矩阵path
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (i == j)
				{
					dist[i][j] = 0;
					path[i][j] = 0;
				}
				else if (arc[i][j] < INF)
				{
					dist[i][j] = arc[i][j];
					path[i][j] = i;
				}
				else
				{
					dist[i][j] = INF;
					path[i][j] = -1;
				}
			}
		}

		for (int k = 0; k < vertexNum; k++)
		{
			for (int i = 0; i < vertexNum; i++)
			{
				for (int j = 0; j < vertexNum; j++)
				{
					if (dist[i][k] != INF && dist[k][j] != INF)
					{
						if (dist[i][j] > dist[i][k] + dist[k][j])
						{
							dist[i][j] = dist[i][k] + dist[k][j];
							path[i][j] = path[k][j];
						}
					}
				}
			}
		}
	}

	void TopoSort()
	{
		std::vector<int> in(vertexNum, 0);
		std::queue<int> q; // 存放入度为0的顶点
		std::vector<int> res; //保存拓扑排序结果
		// 统计顶点入度
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (arc[i][j] != INF && arc[i][j] != 0)
					in[j]++;
			}
		}
		// 把入度为0的点入队
		for (int i = 0; i < vertexNum; i++)
		{
			if (in[i] == 0)
				q.push(i);
		}
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			res.emplace_back(u);
			// 遍历u所有邻接点v, 相当于删掉边u->v
			for (int v = 0; v < vertexNum; v++)
			{
				if (arc[u][v] != INF && arc[u][v] != 0)
				{
					in[v]--;
					if (in[v] == 0)
						q.push(v);
				}
			}
		}

		if (res.size() != vertexNum)
		{
			std::cout << "存在环, 拓扑排序失败\n";
			return;
		}

		std::cout << "拓扑排序: ";
		for (auto x : res)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void DFS(int start)
	{
		std::vector<bool> vis(vertexNum, false);
		std::cout << "DFS: ";
		DfsPrivate(start, vis);
		std::cout << std::endl;
	}

	void BFS(int start)
	{
		std::vector<bool> vis(vertexNum, false);
		std::queue<int> q;
		q.push(start);
		vis[start] = true;
		std::cout << "BFS: ";
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			std::cout << u << " ";
			// 遍历点u的所有邻接点
			for (int v = 0; v < vertexNum; v++)
			{
				// 访问邻接点并入队
				if (arc[u][v] != INF && !vis[v])
				{
					vis[v] = true;
					q.push(v);
				}
			}
		}
		std::cout << std::endl;
	}

	// Critical path of AOE network
	void CriticalPath()
	{
		std::vector<int> topoSeq;
		if (!TopoSortHelper(topoSeq))
		{
			std::cout << "存在环, 无法求解关键路径\n";
			return;
		}

		std::vector<int> ve(vertexNum, 0); //事件的最早发生时间
		// 顺着拓扑序列正向遍历, 计算ve, 取最大值
		for (int u : topoSeq)
		{
			for (int v = 0; v < vertexNum; v++)
			{
				if (arc[u][v] != INF && arc[u][v] != 0)
				{
					if (ve[v] < ve[u] + arc[u][v])
					{
						ve[v] = ve[u] + arc[u][v];
					}
				}
			}
		}

		std::vector<int> vl(vertexNum, ve.back()); // 事件的最晚发生时间
		// 逆着拓扑序列遍历, 计算vl, 取最小值
		for (auto it = topoSeq.rbegin(); it != topoSeq.rend(); it++) // 反向迭代
		{
			int u = *it;
			for (int v = 0; v < vertexNum; v++)
			{
				if (arc[u][v] != INF && arc[u][v] != 0)
				{
					if (vl[u] > vl[v] - arc[u][v])
					{
						vl[u] = vl[v] - arc[u][v];
					}
				}
			}
		}
		std::cout << "\n关键活动：\n";
		// 遍历所有边，计算活动最早开始e、最晚开始l
		for (int u = 0; u < vertexNum; u++)
		{
			for (int v = 0; v < vertexNum; v++)
			{
				if (arc[u][v] != INF && arc[u][v] != 0)
				{
					int e = ve[u];                // 活动<u,v>最早开始时间
					int l = vl[v] - arc[u][v];    // 活动<u,v>最晚开始时间
					if (e == l)
					{                 // e等于l，该活动为关键活动
						std::cout << "<" << u << "," << v << "> 权=" << arc[u][v] << "\n";
					}
				}
			}
		}
		std::cout << "总工期：" << ve.back() << "\n";
	}
};

int main()
{
	std::cout << "===== 无向图测试（DFS、BFS、Prim、Kruskal、Dijkstra、Floyd）=====\n";
	MGraph g1(4, 0);
	g1.AddUDEdge(0, 1, 2);
	g1.AddUDEdge(0, 2, 5);
	g1.AddUDEdge(1, 3, 1);
	g1.AddUDEdge(2, 3, 3);
	g1.Print();
	g1.DFS(0);
	g1.BFS(0);
	g1.Prim();
	g1.Kruskal();
	g1.Dijkstra(0);
	g1.Floyd();

	std::cout << "\n===== AOE有向图测试（拓扑排序、关键路径）=====\n";
	MGraph g2(6, 0);
	g2.AddDEdge(0, 1, 3);
	g2.AddDEdge(0, 2, 2);
	g2.AddDEdge(1, 3, 4);
	g2.AddDEdge(1, 4, 2);
	g2.AddDEdge(2, 4, 3);
	g2.AddDEdge(3, 5, 1);
	g2.AddDEdge(4, 5, 2);
	g2.TopoSort();
	g2.CriticalPath();

	return 0;
}

#elif 0 // Adjacency List Graph

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class ALGraph
{
private:
	struct EdgeNode
	{
		int adjVex;
		int weight;
		EdgeNode* nextEdge;
		EdgeNode(int v, int w) : adjVex(v), weight(w), nextEdge(nullptr) {}
	};

	struct VNode
	{
		int data;
		EdgeNode* firstEdge;
		VNode() : data(0), firstEdge(nullptr) {}
	};

	struct KruskalEdge
	{
		int u, v, w;
		KruskalEdge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
		bool operator<(const KruskalEdge& other) const
		{
			return w < other.w;
		}
	};

	std::vector<VNode> adjList;
	int vertexNum;
	int edgeNum;

private:
	void DfsPrivate(int u, std::vector<bool>& vis)
	{
		std::cout << u << " ";
		vis[u] = true;
		EdgeNode* p = adjList[u].firstEdge;
		while (p)
		{
			int v = p->adjVex;
			if (!vis[v])
			{
				DfsPrivate(v, vis);
			}
			p = p->nextEdge;
		}
	}

	bool TopoSortHelper(std::vector<int>& topoSeq)
	{
		topoSeq.clear(); // 初始化topoSeq
		std::vector<int> in(vertexNum, 0); // 初始化入度
		std::queue<int> q; // 存放入度为0的点
		// 统计各个点的入度
		for (int u = 0; u < vertexNum; u++)
		{
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				in[p->adjVex]++;
				p = p->nextEdge;
			}
		}
		// 将入度为0的点入队
		for (int i = 0; i < vertexNum; i++)
		{
			if (in[i] == 0)
				q.push(i);
		}
		// 删去u->v的边
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			topoSeq.emplace_back(u);
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				in[v]--;
				if (in[v] == 0)
					q.push(v);
				p = p->nextEdge;
			}
		}
		return topoSeq.size() == vertexNum;
	}

	int Find(int x, std::vector<int>& parent)
	{
		if (parent[x] != x)
			parent[x] = Find(parent[x], parent);
		return parent[x];
	}

public:
	static constexpr int INF = 0x3f3f3f3f;

public:
	ALGraph(int n, int e) : vertexNum(n), edgeNum(e)
	{
		adjList.resize(vertexNum);
	}

	~ALGraph()
	{
		for (int i = 0; i < vertexNum; i++)
		{
			EdgeNode* p = adjList[i].firstEdge;
			while (p)
			{
				EdgeNode* q = p;
				p = p->nextEdge;
				delete q;
			}
		}
	}

	void AddUDEdge(int u, int v, int w = 1)
	{
		EdgeNode* p1 = new EdgeNode(v, w);
		p1->nextEdge = adjList[u].firstEdge;
		adjList[u].firstEdge = p1;

		EdgeNode* p2 = new EdgeNode(u, w);
		p2->nextEdge = adjList[v].firstEdge;
		adjList[v].firstEdge = p2;
	}

	void AddDEdge(int u, int v, int w = 1)
	{
		EdgeNode* p = new EdgeNode(v, w);
		p->nextEdge = adjList[u].firstEdge;
		adjList[u].firstEdge = p;
	}

	void Print()
	{
		for (int i = 0; i < vertexNum; i++)
		{
			std::cout << i << " : ";
			EdgeNode* p = adjList[i].firstEdge;
			while (p)
			{
				std::cout << p->adjVex << "(" << p->weight << ") ";
				p = p->nextEdge;
			}
			std::cout << std::endl;
		}
	}

	void DFS(int start)
	{
		std::vector<bool> vis(vertexNum, false);
		std::cout << "DFS: ";
		DfsPrivate(start, vis);
		std::cout << std::endl;
	}

	void BFS(int start)
	{
		std::vector<bool> vis(vertexNum, false);
		std::queue<int> q;
		q.push(start);
		vis[start] = true;

		std::cout << "BFS: ";
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			std::cout << u << " ";
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				if (!vis[v])
				{
					vis[v] = true;
					q.push(v);
				}
				p = p->nextEdge;
			}
		}
		std::cout << std::endl;
	}

	void Dijkstra(int start)
	{
		std::vector<int> dist(vertexNum, INF);
		std::vector<bool> vis(vertexNum, false);
		dist[start] = 0;

		for (int i = 0; i < vertexNum; i++)
		{
			int u = -1;
			int minD = INF;

			for (int j = 0; j < vertexNum; j++)
			{
				if (!vis[j] && dist[j] < minD)
				{
					minD = dist[j];
					u = j;
				}
			}
			if (u == -1)
				break;
			vis[u] = true;
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				if (!vis[v] && dist[v] > dist[u] + p->weight)
				{
					dist[v] = dist[u] + p->weight;
				}
				p = p->nextEdge;
			}
		}
		std::cout << "Dijkstra start= " << start << std::endl;
		for (int i = 0; i < vertexNum; i++)
		{
			if (dist[i] == INF)
				std::cout << i << " : 不可达\n";
			else
				std::cout << i << " : " << dist[i] << std::endl;
		}
	}

	void Floyd()
	{
		std::vector<std::vector<int>> dist(vertexNum, std::vector<int>(vertexNum, INF));
		for (int i = 0; i < vertexNum; i++)
			dist[i][i] = 0;
		// 将邻接表转化为邻接矩阵
		for (int u = 0; u < vertexNum; u++)
		{
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				dist[u][v] = p->weight;
				p = p->nextEdge;
			}
		}
		for (int k = 0; k < vertexNum; k++)
			for (int i = 0; i < vertexNum; i++)
				for (int j = 0; j < vertexNum; j++)
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j])
						dist[i][j] = dist[i][k] + dist[k][j];
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (dist[i][j] >= INF)
					std::cout << "∞ ";
				else
					std::cout << dist[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	void Prim()
	{
		std::vector<int> low(vertexNum, INF);
		std::vector<bool> vis(vertexNum, false);
		low[0] = 0;
		int sum = 0;

		for (int i = 0; i < vertexNum; i++)
		{
			int u = -1;
			int minW = INF;
			for (int j = 0; j < vertexNum; j++)
			{
				if (!vis[j] && low[j] < minW)
				{
					minW = low[j];
					u = j;
				}
			}
			if (u == -1)
			{
				std::cout << "图不连通, 无法生成最小生成树\n";
				return;
			}
			vis[u] = true;
			sum += minW;
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				if (!vis[v] && p->weight < low[v])
				{
					low[v] = p->weight;
				}
				p = p->nextEdge;
			}
		}
		std::cout << "Prim最小生成树权值: " << sum << std::endl;
	}

	void Kruskal()
	{
		std::vector<KruskalEdge> edges;
		std::vector<int> parent(vertexNum);
		int sum = 0;
		int cnt = 0;

		for (int u = 0; u < vertexNum; u++)
		{
			EdgeNode* p = adjList[u].firstEdge;

			while (p)
			{
				if (u < p->adjVex)
				{
					edges.emplace_back(u, p->adjVex, p->weight);
				}
				p = p->nextEdge;
			}
		}
		std::sort(edges.begin(), edges.end());
		
		for (int i = 0; i < vertexNum; i++)
		{
			parent[i] = i;
		}
		
		for (auto& e : edges)
		{
			int fu = Find(e.u, parent);
			int fv = Find(e.v, parent);
			// 判断根是否一致, 不一致说明不会有环
			if (fu != fv)
			{
				parent[fv] = fu;
				sum += e.w;
				cnt++;
				if (cnt == vertexNum - 1)
					break;
			}
		}
		if (cnt != vertexNum - 1)
		{
			std::cout << "图不连通, 无最小生成树\n";
			return;
		}
		std::cout << "Kruskal最小生成树权值和: " << sum << std::endl;
	}

	void TopoSort()
	{
		std::vector<int> res;
		if (!TopoSortHelper(res))
		{
			std::cout << "存在环, 拓扑排序失败\n";
			return;
		}
		std::cout << "拓扑排序: ";
		for (auto x : res)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void CriticalPath()
	{
		std::vector<int> topoSeq;
		std::vector<int> ve(vertexNum, 0);
		std::vector<int> vl(vertexNum, ve.back());

		if (!TopoSortHelper(topoSeq))
		{
			std::cout << "存在环, 无法求解关键路径\n";
			return;
		}
		// 求出ve[u]
		for (int u : topoSeq)
		{
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				if (ve[v] < ve[u] + p->weight)
				{
					ve[v] = ve[u] + p->weight;
				}
				p = p->nextEdge;
			}
		}
		// 求出vl[u]
		for (auto it = topoSeq.rbegin(); it != topoSeq.rend();it++)
		{
			int u = *it;
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				if (vl[u] > vl[v] - p->weight)
				{
					vl[u] = vl[v] - p->weight;
				}
				p = p->nextEdge;
			}
		}
		std::cout << "\n关键活动: \n";

		for (int u = 0; u < vertexNum; u++)
		{
			EdgeNode* p = adjList[u].firstEdge;
			while (p)
			{
				int v = p->adjVex;
				int e = ve[u];
				int l = vl[v] - p->weight;
				if (e == l)
				{
					std::cout << "<" << u << "," << v << "> 权=" << p->weight << std::endl;
				}
				p = p->nextEdge;
			}
		}
		std::cout << "总工期: " << ve.back() << std::endl;
	}
};

int main()
{
	std::cout << "===== 无向图测试（Prim、Kruskal、DFS、BFS、Dijkstra、Floyd）=====\n";
	ALGraph g1(4, 5);
	g1.AddUDEdge(0, 1, 2);
	g1.AddUDEdge(0, 2, 5);
	g1.AddUDEdge(1, 2, 1);
	g1.AddUDEdge(1, 3, 4);
	g1.AddUDEdge(2, 3, 2);
	g1.Print();
	g1.DFS(0);
	g1.BFS(0);
	g1.Dijkstra(0);
	g1.Prim();
	g1.Kruskal();
	std::cout << "Floyd最短路矩阵：\n";
	g1.Floyd();

	std::cout << "\n===== 有向图AOE网测试（拓扑排序、关键路径）=====\n";
	ALGraph g2(6, 8);
	g2.AddDEdge(0, 1, 3);
	g2.AddDEdge(0, 2, 2);
	g2.AddDEdge(1, 3, 4);
	g2.AddDEdge(1, 4, 2);
	g2.AddDEdge(2, 4, 3);
	g2.AddDEdge(3, 5, 2);
	g2.AddDEdge(4, 3, 1);
	g2.AddDEdge(4, 5, 3);
	g2.Print();
	g2.TopoSort();
	g2.CriticalPath();

	return 0;
}

#endif 
