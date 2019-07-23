
public class LongestIncreasingSubsequence {
	public static int lis(int[] list) {
		int n = list.length;
		int[] dp = new int[n];
		dp[0] = 1;
		int res = 0;
		for (int i=1; i<n; i++) {
			dp[i] = 1;
			for (int j=0; j<i; j++) {
				if (list[j] < list[i]) dp[i] = Math.max(dp[i], dp[j]+1);
			}
			res = Math.max(res, dp[i]);
		}
		return res;
	}

}
