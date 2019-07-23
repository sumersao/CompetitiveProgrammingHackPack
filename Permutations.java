
public class Permutations {
	public static void RecPerm(int[] perm, int [] vals, boolean[] used, int k) {
		if (k == perm.length) {

		}
		else {
			for (int i=0; i<perm.length; i++) {
				if (!used[i]) {
					perm[k] = vals[i];
					used[i] = true;
					RecPerm(perm, vals, used, k+1);
					used[i] = false;
				}
			}
		}
	}

}
