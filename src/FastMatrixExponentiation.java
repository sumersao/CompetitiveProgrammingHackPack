public class FastMatrixExponentiation {
	public static long mod= 1000000007L;
	public static void main(String[] args) {
		long [][] a= new long [][]{{1L,1L},{1L,0L}};
		long [][] res= expo(a,3000);
		System.out.println(res[0][0]);
	}
	public static long [][] expo(long [][] m, long pow){
		if(pow==0L) return identity(m.length);
		if(pow%2==0) {
			long [][] res= expo(m, pow/2);
			return mult(res,res);
		}
		return mult(m, expo(m, pow-1));
	}
	public static long [][] identity(int n){
		long [][] res= new long[n][n];
		for (int i = 0; i < res.length; i++) {
			res[i][i]= 1L;
		}
		return res;
	}
	public static long [][] mult(long [][] a, long [][] b){
		int n= a.length;
		long [][] res= new long[n][n];
		for (int i = 0; i < res.length; i++) {
			for (int j = 0; j < res.length; j++) {
				for (int k = 0; k < res.length; k++) {
					res[i][j]= (res[i][j]+a[i][k]*b[k][j])%mod;
				}
			}
		}
		return res;
	}
}
