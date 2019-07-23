import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

//Mo's Algorithm
public class Mo {
	public static int b;
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		int n= in.nextInt();
		int q= in.nextInt();
		query [] qq= new query[q];
		int [] a= new int[n];
		for (int i = 0; i < a.length; i++) {
			a[i]= in.nextInt();
		}
		b= (int) Math.sqrt(n)+1;
		for (int i = 0; i < q; i++) {
			int l= in.nextInt()-1;
			int r= in.nextInt()-1;
			qq[i]= new query(l, r, i);
		}
		Arrays.sort(qq);
		int [] f= new int[1000001];
		int cl=0, cr= 0, len=0;
		int [] res= new int[q];
		for (int i = 0; i < q; i++) {
			int l= qq[i].l;
			int r= qq[i].r;
			
			while(cl<l) {
				f[a[cl]]--;
				if(f[a[cl]]==0) len--;
				cl++;
			}
			while(cl>l) {
				cl--;
				f[a[cl]]++;
				if(f[a[cl]]==1) len++;
			}
			while(cr<=r) {
				f[a[cr]]++;
				if(f[a[cr]]==1) len++;
				cr++;
			}
			while(cr>r+1) {
				cr--;
				f[a[cr]]--;
				if(f[a[cr]]==0) len--;
			}
			res[qq[i].id]= len;
		}
		for(int cur : res) {
			System.out.println(cur);
		}	
	}
	


static class query implements Comparable <query>{
		public int l, r, id;
		public query(int a, int b, int c) {
			l = a;
			r = b;
			id= c;
		}
		public int compareTo(query o) {
			int thing= l/b;
			int thing1= o.l/b;
			if (thing != thing1) {
				return thing-thing1;
			} 
			if((thing&1)==1) {
				return r-o.r;
			}
			return o.r-r;
		}
	}
}
