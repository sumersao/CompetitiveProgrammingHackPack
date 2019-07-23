import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

public class Dijkstra {
	public static void main(String[] args) {
		int n = 10;
		ArrayList<edge>[] adj = new ArrayList[n];
		PriorityQueue<edge> pq = new PriorityQueue<>();
		int [] dist= new int[n];
		Arrays.fill(dist, 123456789);
		dist[0]=0;
		pq.offer(new edge(0,0));
		while(!pq.isEmpty()) {
			edge cur= pq.poll();
			for(edge nex: adj[cur.to]) {
				if(dist[cur.to]+nex.w<dist[nex.to]) {
					pq.offer(nex);
					dist[nex.to]= dist[cur.to]+nex.w;
				}
			}
		}
	}
	static class edge implements Comparable<edge>{
		int to, w;
		public edge(int a, int b) {
			to=a;
			w=b;
		}
		public int compareTo(edge o) {
			return this.w-o.w;
		}
	}
}
