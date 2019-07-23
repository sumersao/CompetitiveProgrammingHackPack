import java.util.ArrayList;
import java.util.Arrays;

public class NumberTheory {
	public static int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	public static int lcm(int a, int b) {
		return (a * b) / gcd(a, b);
	}
	public static int [] p;
	public static void numberSieve(int n){
		p= new int[n+1];
		for (int i = 1; i <= n; i++) p[i]=i;
		for (int i = 2; i <= n; i++) {
			if(p[i]==i) {
				for (int j = 2*i; j <= n; j+=i) {
					p[j]= i;
				}
			}
		}
	}
	//uses p[] array from above
	public static ArrayList<Integer> primefactors(int x){
		ArrayList<Integer> pfactors= new ArrayList<Integer>();
		while(x>1){
			pfactors.add(p[x]);
			x/=p[x];
		}
		return pfactors;
	}
	//Prime factors of a number
	public static ArrayList<Integer> primeFactors(int numbers) {
		int n = numbers;
		ArrayList<Integer> factors = new ArrayList<Integer>();
		for (int i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				factors.add(i);
				n /= i;
			}
		}
		if (n > 1) {
			factors.add(n);
		}
		return factors;
	}
	//Whether or not a number is prime in the isPrime array.
	public static void PrimeSieve(int max){
		boolean[] isPrime = new boolean[max+1];
		Arrays.fill(isPrime, true);
		isPrime[0] = false;
		isPrime[1] = false;
		for (int i=2; i<max; i++){
			for (int j=i*i; j<max; j+=i){
				isPrime[j] = false;
			}
		}
	}
	//Extended Euclidean Princeton
	public static int[] EE(int p, int q) {
		if (q == 0)
			return new int[] { p, 1, 0 };
		int[] vals = EE(q, p % q);
		int d = vals[0];
		int a = vals[2];
		int b = vals[1] - (p / q) * vals[2];
		return new int[] { d, a, b };
	}
	//Extended Euclidean Kirsche
	public static int [] ee(int a, int b){
		if(a>b) return ee(b,a);
		if(a==0) return new int[] {0,1};
		int q= b/a;
		int r= b%a;
		int [] res= ee(r,a);
		return new int [] {res[1]-q*res[0], res[0]};
	}
	public static int modinv(int a, int m){
		int [] res= ee(a, m);
		return (res[0]+m)%m;
	}
}