import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Kosaraju {
	public static ArrayList<Integer> [] adj, rev;
	public static int n;
	public static boolean [] vis;
	public static int [] w;
	public static ArrayDeque<Integer> stack;
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		n= in.nextInt();
		int m= in.nextInt();
		vis= new boolean[n];
		adj= new ArrayList[n];
		rev= new ArrayList[n];
		stack = new ArrayDeque<>();
		for (int i = 0; i < n; i++) {
			adj[i]= new ArrayList<>();
			rev[i]= new ArrayList<>();
		}
		for (int i = 0; i < m; i++) {
			int a= in.nextInt()-1;
			int b= in.nextInt()-1;
			adj[a].add(b);
			rev[b].add(a);
		}
		for (int i = 0; i < n; i++) {
			dfs(i);
		}
		int numscc=0;
		int [] sccid= new int[n];
		Arrays.fill(sccid, -1);
		while(!stack.isEmpty()) {
			int cur= stack.pop();
			
			if(sccid[cur]!=-1) continue;
			
			sccid[cur]= numscc;
			ArrayDeque<Integer> q = new ArrayDeque<>();
			q.offer(cur);
			while(!q.isEmpty()) {
				int on= q.poll();
				for(int nex: rev[on]) {
					if(sccid[nex]==-1) {
						q.offer(nex);
						sccid[nex]= numscc;
					}
				}
			}
			numscc++;
		}
		w= new int[numscc];
		for (int i = 0; i < sccid.length; i++) {
			w[sccid[i]]++;
		}
		ArrayList<Integer>[] dage= DAG(sccid, numscc);
		ArrayList<Integer>[] dagrev= new ArrayList[numscc];
		for (int i = 0; i < dagrev.length; i++) {
			dagrev[i]= new ArrayList<>();
		}
		
		for (int i = 0; i < dagrev.length; i++) {
			for(int nex: dage[i]) {
				dagrev[nex].add(i);
			}
		}
	}
	public static void dfs(int on) {
		if(vis[on]) return;
		vis[on]=true;
		for(int nex: adj[on]) {
			dfs(nex);
		}
		stack.push(on);
	}
	public static ArrayList<Integer>[] DAG(int [] sccid, int n){
		ArrayList<Integer>[] b= new ArrayList[n];
		for (int i = 0; i < b.length; i++) {
			b[i]= new ArrayList<>();
		}
		for (int i = 0; i < sccid.length; i++) {
			int x= sccid[i];
			for(int y: adj[i]) {
				if(x!=sccid[y]) {
					b[x].add(sccid[y]);
				}
			}
		}
		return b;
	}
}
