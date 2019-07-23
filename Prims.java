import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Prims {
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		int n= in.nextInt();
		int m= in.nextInt();
		boolean [] vis= new boolean[n];
		ArrayList<e>[] adj= new ArrayList[n];
		for (int i = 0; i < adj.length; i++) {
			adj[i]= new ArrayList<>();
		}
		for (int i = 0; i < m; i++) {
			int a= in.nextInt()-1;
			int b= in.nextInt()-1;
			int c= in.nextInt();
			adj[a].add(new e(b,c));
			adj[b].add(new e(a,c));
		}
		PriorityQueue<e> pq= new PriorityQueue<>();
		for (int i = 0; i < adj[0].size(); i++) {
			pq.offer(adj[0].get(i));
		}
		vis[0]= true;
		long mst=0;
		while(!pq.isEmpty()) {
			e cur = pq.poll();
			if(vis[cur.to]) continue;
			vis[cur.to]= true;
			mst+= cur.w;
			for(e nex: adj[cur.to]) {
				pq.add(nex);
			}
		}
		System.out.println(mst);
	}
	static class e implements Comparable<e>{
		int to, w;
		public e(int a, int b) {
			to= a;
			w= b;
		}
		public int compareTo(e o) {
			return this.w- o.w;
		}
	}
}
