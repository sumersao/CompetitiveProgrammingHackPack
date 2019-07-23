
public class DisjointSet {
	public static int [] height, par;
	public static int numc;
	public DisjointSet(int n) {
		height= new int[n];
		par= new int[n];
		for (int i = 0; i < n; i++) {
			par[i]= i;
		}
		numc=n;
	}
	public static int find(int on) {
		if(par[on]==on) return on;
		return find(par[on]);
	}
	public static void merge(int a, int b) {
		int seta= find(a);
		int setb= find(b);
		//in same set already
		if(seta==setb) return;
		if(height[seta]<height[setb]) {
			par[seta]= setb;
		}
		else if(height[seta]>height[setb]) {
			par[setb]=seta;
		}
		else {
			par[seta]= setb;
			height[setb]++;
		}
		numc--;
	}
}
