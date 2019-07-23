
public class BinaryIndexedTree {
	static class FenwickTree {
		long[] ft;
		public FenwickTree(int n) {
			ft = new long[n + 1];
		}
		long rsq(int b) {
			long sum = 0;
			for (; b > 0; b -= (b & (-b))) sum += ft[b];
			return sum;
		}
		long rsq(int a, int b) {
			return rsq(b) - rsq(a - 1);
		}
		void update(int k, long v) {
			for (; k < ft.length; k += (k & (-k))) ft[k] += v;
		}
	}
}
