public class SegmentTreeArrays{
	int n;
	int [] lo, hi, min, delta;
	public SegmentTreeArrays(int a) {
		n=a;
		lo= new int[4*n+1];
		hi= new int[4*n+1];
		min= new int[4*n+1];
		delta= new int[4*n+1];
		init(1, 0, n-1);
	}
	public void init(int i, int a, int b) {
		lo[i]= a;
		hi[i]= b;
		if(a==b) return;
		int mid= (a+b)/2;
		init(2*i, a, mid);
		init(2*i, mid+1, b);
	}
	public void increment(int a, int b, int val) {
		increment(1, a, b, val);
	}
	public void increment(int i, int a, int b, int val) {
		if(b<lo[i] || a>hi[i]) return;

		if(a<=lo[i] && b>= hi[i]) {
			delta[i]+=val;
			return;
		}
		prop(i);

		increment(2*i, a, b, val);
		increment(2*i+1, a, b, val);

		update(i);
	}
	public int min(int a, int b) {
		return min(1, a, b);
	}
	public int min(int i, int a, int b) {
		if(b<lo[i]||hi[i] <a) return Integer.MAX_VALUE;
		if(a<=lo[i] && b>= hi[i]) return min[i]+ delta[i];

		prop(i);

		int minleft= min(2*i, a, b);
		int minright= min(2*i+1, a,b);

		update(i);

		return Math.min(minleft, minright);
	}
	//lazy
	public void prop(int i) {
		delta[2*i]+= delta[i];
		delta[2*i+1]+= delta[i];
		delta[i]=0;
	}
	public void update(int i) {
		min[i]= Math.min(min[2*i]+delta[2*i], min[2*i+1]+delta[2*i+1]);
	}
}
