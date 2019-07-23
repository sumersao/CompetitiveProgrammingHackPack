public class SegmentTreeNode {
	static class node{
		long sum, lazy, mini;
		node l, r;
		int lo,hi, m;
		public node(int a, int b) {
			lo= a;
			hi=b;
			sum=0;
			mini= 0;
			m= (lo+hi)/2;
			if(lo!=hi) {
				l= new node(a, m);
				r= new node(m+1,b);
				return;
			}
			l= null;
			r= null;
		}
		public void add(int s, int e, long x) {
			//push();
			if(s<=lo&&hi<=e) {
				lazy+=x;
				mini+=x;
				sum+= (long) (hi-lo+1)*x;
				return;
			}
			push();
			if(s<=m) {
				l.add(s, e, x);
			}
			if(e>m) {
				r.add(s, e, x);
			}
			sum= l.sum+r.sum;
			mini= Math.min(l.mini, r.mini);
		}
		public long getsum(int s, int e) {
			push();
			if(s<=lo&&hi<=e) {
				return sum;
			}
			long res=0;
			if(s<=m) {
				res+= l.getsum(s, e);
			}
			if(e>m){
				res+= r.getsum(s, e);
			}
			return res;
		}
		public long getmini(int s, int e) {
			push();
			if(s<=lo&&hi<=e) {
				return mini;
			}
			long res=1234567890L;
			if(s<=m) {
				res= Math.min(res, l.getmini(s, e));
			}
			if(e>m){
				res= Math.min(res, r.getmini(s, e));
			}
			return res;
		}
		public void push() {
			if(lo!=hi) {
				l.lazy+= lazy;
				l.sum+= (l.hi-l.lo+1)*lazy;
				l.mini+= lazy;

				r.lazy+= lazy;
				r.sum+= (r.hi-r.lo+1)*lazy;
				r.mini+=lazy;
			}
			lazy=0;
		}
		public int kth(int k) {
			if(lo==hi) return lo;
			push();
			if(l.sum>=k) {
				return l.kth(k);
			}
			else {
				k-= l.sum;
				return r.kth(k);
			}
		}
	}
}
