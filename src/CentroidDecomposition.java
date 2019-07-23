import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

public class CentroidDecomposition {
	public static ArrayList<edge>[] adj;
	public static int [] parent, subtreesum;
	public static boolean [] blocked;
	public static ArrayDeque<Integer> q= new ArrayDeque<>();
	public static int k, ans, n;
	public static HashMap<Integer, Integer> res = new HashMap<>();
	public static int findcentroid(int entrypoint) {
		calcsum(entrypoint, entrypoint);
		int centroid= entrypoint;
		int bestsize= subtreesum[entrypoint];
		int compsize= 0;
		q.add(entrypoint);
		while(q.size()>0) {
			int cur= q.poll();
			compsize++;
			int size = subtreesum[entrypoint]- subtreesum[cur];
			
			for(edge nex: adj[cur]) {
				if(nex.to!= parent[cur] &&!blocked[nex.to]) {
					size= Math.max(size, subtreesum[nex.to]);
					q.add(nex.to);
				}
			}
			if(size<bestsize) {
				centroid= cur;
				bestsize= size;
			}
		}
		return centroid;
	}
	public static void go(int aa) {
		int on= findcentroid(aa);
		if(blocked[on]) return;
		blocked[on]= true;
	}
	public static void calcsum(int on, int p) {
		parent[on]= p;
		subtreesum[on]= 1;
		for(edge nex: adj[on]) {
			if(nex.to!= p && !blocked[nex.to]) {
				calcsum(nex.to, on);
				subtreesum[on]+= subtreesum[nex.to];
			}
		}
	}
	static class edge{
		int to, w;
		public edge(int a, int b) {
			to= a;
			w=b;
		}
	}
}
