public class Combinations {
	public static long [][] choose= new long[100001][11];
	public static long mod= 1000000007L;
	public static void go() {
		for (int i = 0; i < 11; i++) {
			choose[i][0]=1L;
			choose[i][i]=1L;
		}
		for (int i = 1; i < choose.length; i++) {
			for (int j = 1; j < 11; j++) {
				if(j==i) break;
				choose[i][j]= (choose[i-1][j-1]+ choose[i-1][j])%mod;
			}
		}
	}
}
