import java.util.ArrayList;

public class Subsets {
	public static void main(String[] args) {
		int n= 12;
		int [] a= new int[n];
		for (int i=0; i < (1<<n); i++) {
		    ArrayList<Integer> subset= new ArrayList<>();
		    for (int k=0; k < n; k++) {
		        if ((i&(1<<k)) > 0){
		        	subset.add(a[k]);
		        }
		    }
		}
	}

}
