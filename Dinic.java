import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;

public class Dinic{
	class edge{
		int v1, v2, cap, flow;
		edge rev;
		public edge(int a, int b, int c, int d) {
			v1= a;
			v2= b;
			cap= c;
			flow= d;
		}
	}

	ArrayDeque<Integer> q;
	ArrayList<edge>[] adj;
	int n, s, t, oo= 123456789;
	boolean [] blocked;
	int [] dist;

	public Dinic(int a) {
		n= a;
		s= n++;
		t= n++;
		blocked= new boolean[n];
		dist= new int[n];
		q= new ArrayDeque<>();
		adj= new ArrayList[n];
		for (int i = 0; i < adj.length; i++) {
			adj[i]= new ArrayList<>();
		}
	}
	public void add(int a, int b, int cap, int flow) {
		edge e= new edge(a, b, cap, flow);
		edge rev= new edge(b,a,0,0);
		adj[a].add(rev.rev=e);
		adj[b].add(e.rev= rev);
	}
	public boolean bfs() {
		q.clear();
		Arrays.fill(dist, -1);
		dist[t] = 0;
		q.add(t);

		while (!q.isEmpty()) {
			int cur = q.poll();
			if (cur == s) return true;
			for (edge e : adj[cur]) {
				if (e.rev.cap > e.rev.flow && dist[e.v2] == -1) {
					dist[e.v2] = dist[cur] + 1;
					q.add(e.v2);
				}
			}
		}
		return dist[s] != -1;
	}

	public int dfs(int on, int min) {
		if (on == t) return min;
		int flow = 0;
		for (edge e : adj[on]) {
			int cur = 0;
			if (!blocked[e.v2] && dist[e.v2] == dist[on] - 1 && e.cap - e.flow > 0) {
				cur = dfs(e.v2, Math.min(min - flow, e.cap - e.flow));
				e.flow += cur;
				e.rev.flow = -e.flow;
				flow += cur;
			}
			if (flow == min) return flow;
		}
		blocked[on] = flow != min;
		return flow;
	}

	public int flow() {
		clear();
		int ret = 0;
		while (bfs()) {
			Arrays.fill(blocked, false);
			ret += dfs(s, oo);
		}
		return ret;
	}

	public void clear() {
		for (ArrayList<edge> edges : adj) {
			for (edge e : edges) {
				e.flow = 0;
			}		
		}
	}
}
