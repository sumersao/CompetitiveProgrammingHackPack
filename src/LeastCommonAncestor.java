import java.util.ArrayList;

public class LeastCommonAncestor {
	
	public static int [][] jump= new int[19][100010];
	public static int [] d= new int[100010];
	public static int [] par= new int[100010];
	boolean [] vis = new boolean[100010];
	public static ArrayList<Integer>[] adj;
	public static int n;
	
	public static void main(String[] args) {
		par[0]=-1;
		go(0,-1);
		
		for (int i = 0; i < n; i++) {
			jump[0][i]= par[i];
		}
		for (int i = 1; i < 19; i++) {
			for (int j = 0; j < n; j++) {
				if(jump[i-1][j]==-1) jump[i][j]= -1;
				else jump[i][j]= jump[i-1][jump[i-1][j]];
			}
		}
	}
	public static int lca(int a, int b) {
		//a is the higher one in the tree
		if(d[a]<d[b]) {
			int temp= a;
			a=b;
			b=temp;
		}
		for(int i=18; i>=0; i--) {
			int to= jump[i][a];
			if(to!=-1 && d[to]>=d[b]) {
				a= to;
			}
		}
		if(a==b) return a;
		for(int i=18; i>=0; i--) {
			int toa= jump[i][a];
			int tob= jump[i][b];
			if(toa==-1||tob==-1) continue;
			if(toa!=tob) {
				a=toa;
				b=tob;
			}
		}
		return jump[0][a];
	}
	public static void go(int on, int p) {
		for(int nex: adj[on]) {
			if(p==nex) continue;
			par[nex]= on;
			d[nex]= d[par[nex]]+1;
			go(nex, on);
		}
	}
}
