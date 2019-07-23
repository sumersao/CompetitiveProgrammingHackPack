import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class DFS_Lowlink1 {
	public static int [] pre, low;
	public static graph g;
	public static int count=0;
	public static ArrayList<Integer> bridges= new ArrayList<>();
	public static boolean [] artp;
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		int n= in.nextInt();
		g= new graph(n);
		pre= new int[n];
		low= new int[n];
		artp= new boolean[n];
		Arrays.fill(pre, -1);
		
		for (int i = 0; i < n; i++) {
			if(pre[i]==-1) dfs(i, i, g.m);
		}
	}
	public static int dfs(int on, int par, int id) {
		//backedge
		if(pre[on]!=-1) {
			low[par]= Math.min(low[par], pre[on]);
			return low[par];
		}
		pre[on]= count++;
		low[on]= pre[on];
		boolean hasfwd= false;
		for(edge nex: g.adj[on]) {
			if(nex.id==id) continue;
			if(dfs(nex.j, on, nex.id)<0) {
				low[on]= Math.min(low[on], low[nex.j]);
				if(low[nex.j]==pre[nex.j]) {
					bridges.add(nex.id);
				}	
				if(on!= par ? low[nex.j] >= pre[on] : hasfwd) {
					artp[on]= true;
				}
				hasfwd= true;	
			}
		}
		return -1;
	}
	static class graph{
		int n, m;
		ArrayList<edge>[] adj;
		public graph(int a) {
			n= a;
			m=0;
			adj= new ArrayList[n];
			for (int i = 0; i < adj.length; i++) {
				adj[i]= new ArrayList<>();
			}
		}
		public void add(int i, int j) {
			adj[i].add(new edge(j,m));
			adj[j].add(new edge(i,m));
			m++;
		}
	}
	static class edge{
		int j, id;
		public edge(int a, int b) {
			j=a;
			id= b;
		}
	}
}
