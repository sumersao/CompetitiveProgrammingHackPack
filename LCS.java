
public class LCS {
	public static char[] str1;
	public static char[] str2;
	public static int[][] memo;
	public static int findLCS(int len1, int len2) {
		if (len1 == 0 || len2 == 0){
			return 0;
		}
		if (memo[len1][len2] != -1){
			return memo[len1][len2];
		}
		if (str1[len1-1] == str2[len2-1]){
			return memo[len1][len2] = 1 + findLCS(len1-1, len2-1);
		}
		return memo[len1][len2] = Math.max(findLCS(len1, len2-1), findLCS(len1-1, len2));
	}

}
