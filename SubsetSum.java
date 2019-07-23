
public class SubsetSum {
	public static boolean subset(int[] array, int target) {
		boolean[] hasSum = new boolean[target + 1];
		hasSum[0] = true;
		for (int i = 0; i < array.length; i++) {
			for (int j = target; j >= array[i]; j--) {
				if (hasSum[j - array[i]]) {
					hasSum[j] = true;
				}
			}
		}
		return hasSum[target];
	}

}
