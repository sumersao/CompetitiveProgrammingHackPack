import java.util.ArrayList;

public class DFS_Lowlink2 {
	public static int [] pre, low;
	public static int count;
	public static boolean [] vis;
	public static ArrayList<Integer>[] adj;
	public static void go(int on, int par) {
		pre[on]= count++;
		low[on]= pre[on];
		vis[on]= true;
		boolean isart= false;
		int childcount=0;
		for(int nex: adj[on]) {
			if(nex==par) continue;
			if(vis[nex]) {
				low[on] = Math.min(low[on], pre[on]);
			}
			else {
				childcount++;
				go(nex, on);
				low[on]= Math.min(low[on], low[nex]);
				if(low[nex]>=pre[on]) {
					isart= true;
				}
				if(pre[on]<low[nex]) {
					System.out.println("bridge");
				}
			}
		}
		if(par==-1) {
			isart= childcount!=1? true:false;
		}
		if(isart) {
			System.out.println("Art"+ on);
		}
	}
}
