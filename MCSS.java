
public class MCSS {
	//O(n) Maximum contiguous subsequence
	public static int mcss(int[] vals) {
		int max = 0, sum = 0, start = 0, end = 0, i = 0;
		for (int j = 0; j < vals.length; j++) {
			sum += vals[j];
			if (sum > max) {
				max = sum;
				start = i;
				end = j;
			} else if (sum < 0) {
				i = j + 1;
				sum = 0;
			}
		}
		return max;
	}
}
