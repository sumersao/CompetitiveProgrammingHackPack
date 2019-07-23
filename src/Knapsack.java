
public class Knapsack {
	public static int[] knap(int[] weights, int[] values, int target) {
		int[] dp = new int[target+1];
		for (int i=0; i<weights.length; i++){
			for (int j=target; j>=weights[i]; j--){
				if (dp[j-weights[i]] + values[i] > dp[j]){
					dp[j] = dp[j-weights[i]] + values[i];
				}
			}
		}
		return dp;
	}
}
