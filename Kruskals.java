import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Kruskals {
	public static ArrayList<edge> adj;
	public static int n;
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int m = in.nextInt();
		adj= new ArrayList<>();
		
		for (int i = 0; i < m; i++) {
			int a = in.nextInt()-1;
			int b = in.nextInt()-1;
			int w = in.nextInt();
			adj.add(new edge(a,b,w));
		}
		
		Collections.sort(adj);
		
		DisjointSet dj= new DisjointSet(n);
		
		int nume=0;
		long mst= 0;
		int i=0;
		while(nume<n-1) {
			edge cur= adj.get(i);
			i++;
			boolean flag= dj.merge(cur.v1, cur.v2);
			if(!flag) continue;
			mst+= cur.w;
			nume++;
		}
		System.out.println(mst);
	}
	static class edge implements Comparable<edge> {
		int v1, v2, w;

		public edge(int vbeg, int vend, int ww) {
			v1 = vbeg;
			v2 = vend;
			w = ww;
		}

		public int compareTo(edge o) {
			return this.w- o.w;
		}
	}
}
