
public class Catalan {
	public static void main(String[] args) {
		long[] catalan = new long[1001];
		catalan[0] = 1L;
		catalan[1] = 1L;
		catalan[2] = 2L;
		for (int i=3; i<=catalan.length; i++){
			for (int j=0; j<i; j++){
				catalan[i] = (catalan[i] + catalan[j]*catalan[i-1-j])%1000000;
			}
		}
	}

}
