
public class FloydWarshall {
	public static int[][] shortestpath(int[][] adj) {
		int n = adj.length;
		for(int k=0; k<n; k++)
			for(int i=0; i<n; i++)
				for(int j=0; j<n; j++)
					adj[i][j] = Math.min(adj[i][j], adj[i][k]+adj[k][j]);
		return adj;
	}
}
