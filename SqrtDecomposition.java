import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class SqrtDecomposition {
	public static int n, q, size;
	public static int [] rt;
	public static long [] a, lazy, sum, min;
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		n= in.nextInt();
		q= in.nextInt();
		a= new long[n];
		rt= new int[n];
		
		for (int i = 0; i < n; i++) {
			a[i]= in.nextLong();
		}
		size= (int) Math.sqrt(n)+1;
		
		for (int i = 0; i < n; i++) {
			rt[i] = i/size;
		}
		sum= new long[size+1];
		lazy= new long[size+1];
		min= new long[size+1];
		Arrays.fill(min, Integer.MAX_VALUE);
		for (int i = 0; i < n; i++) {
			sum[rt[i]]+= a[i];
			min[rt[i]]= Math.min(min[rt[i]], a[i]);
		}
	}
	public static long getsum(int l, int r) {
		int lb= rt[l], rb= rt[r];
		long tot=0;
		if(lazy[lb]!=0) push(lb);
		while(l<=r&&rt[l]==lb) {
			tot+= a[l];
			l++;
		}
		if(lazy[rb]!=0) push(rb);
		while(r>=l&&rt[r]==rb) {
			tot+= a[r];
			r--;
		}
		if(l<r) {
			for (int i = rt[l]; i <= rt[r]; i++) {
				tot+= sum[i];
			}
		}
		return tot;
	}
	public static long getmin(int l, int r) {
		int lb= rt[l], rb= rt[r];
		long res=Long.MAX_VALUE;
		if(lazy[lb]!=0) push(lb);
		while(l<=r&&rt[l]==lb) {
			res= Math.min(res, a[l]);
			l++;
		}
		if(lazy[rb]!=0) push(rb);
		while(r>=l&&rt[r]==rb) {
			res= Math.min(res, a[r]);
			r--;
		}
		if(l<r) {
			for (int i = rt[l]; i <= rt[r]; i++) {
				res= Math.min(res, min[i]);
			}
		}
		return res;
	}
	public static void add(int l, int r, int v) {
		int lb= rt[l], rb= rt[r];
		while(l<=r&&rt[l]==lb) {
			a[l]+=v;
			sum[rt[l]]+= v;
			l++;
		}
		while(r>=l&&rt[r]==rb) {
			a[r]+=v;
			sum[rt[r]]+= v;
			r--;
		}
		//update mins
		updmin(lb);
		updmin(rb);
		if(l<r) {
			for (int i = rt[l]; i <= rt[r]; i++) {
				lazy[i]+= v;
				sum[i]+= (long)(size*v);
				min[i]+=v;
			}
		}
		
	}
	//push my partial bucket updates
	public static void push(int b) {
		for (int i = b*size; i<n&&rt[i]==b; i++) {
			a[i]+= lazy[b];
		}
		lazy[b]=0;
	}
	public static void updmin(int b) {
		if(lazy[b]!=0) push(b);
		long mini= Long.MAX_VALUE;
		for (int i = b*size; i<n&&rt[i]==b; i++) {
			mini= Math.min(mini, a[i]);
		}
		min[b]= mini;
	}
}
