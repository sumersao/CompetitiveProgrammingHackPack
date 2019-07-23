public class GaussianElimination {
	public static double [][] eqnsorig, eqns;
	public static int n;
	public static void main(String[] args) {
		boolean res= getRowEschelon();
		double [] ans= go();
	}
	public static int getMaxRow(int varI) {
		int res= varI;
		for (int i = varI+1; i < n; i++) {
			if(Math.abs(eqns[i][varI]) > Math.abs(eqns[res][varI])) res= i;
		}
		return res;
	}
	public static void swapRows(int i, int j) {
		double [] temp = eqns[i];
		eqns[i]= eqns[j];
		eqns[j]= temp;
	}
	public static void reduce(int i, int j) {
		double factor= eqns[j][i]/eqns[i][i];
		for (int k = i; k <= n; k++) {
			eqns[j][k]= eqns[j][k]-factor*eqns[i][k];
		}
	}
	public static boolean getRowEschelon() {
		for (int i = 0; i < n-1; i++) {
			int best= getMaxRow(i);
			swapRows(i, best);
			if(Math.abs(eqns[i][i])<1e-9) return false;
			for (int j = i+1; j < n; j++) {
				reduce(i,j);
			}			
		}
		return true;
	}
	public static double [] go() {
		double [] res= new double[n];
		for (int i = n-1; i >=0; i--) {
			double c= eqns[i][n];
			for (int j = i+1; j < n; j++) {
				c-= eqns[i][j]*res[j];
			}
			res[i]= c/eqns[i][i];
		}
		return res;
	}
}
