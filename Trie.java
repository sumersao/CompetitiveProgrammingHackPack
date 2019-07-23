import java.util.Scanner;

public class Trie {
	public static String [] input;
	public static int [] alph= new int[26];
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		int n= in.nextInt();
		input= new String[n];
		for (int i = 0; i < n; i++) input[i]= in.next();
		for (int i = 0; i < alph.length; i++) {
			alph[i]= i;
		}
		node trie= new node();
		for (int i = 0; i < input.length; i++) {
			trie.add(0, i, input[i].toCharArray());
		}
		for (int i = 1; i <= 9; i++) {
			System.out.println(trie.query(i));
		}
	}
	static class node{
		//size is how many words pass through me, id is what word i am related to the input
		//term represents how many words end here
		int size, id, term;
		node [] children;
		public node() {
			size=0;
			term=0;
			children= new node[26];
		}
		//adds a word to my trie
		public void add(int ind, int ii, char [] word) {
			size++;
			if(ind==word.length) {
				term++;
				id= ii;
				return;
			}
			int c= word[ind]-'a';
			if(children[c]==null) {
				children[c]= new node();
			}
			children[c].add(ind+1, ii, word);
		}
		
//finds the lexicographically kth string according to alph
		String query(int k) {
			if(term>=k) return input[id];
			
			int tot= term;
			for(int i: alph) {
				if(children[i]==null) continue;
				if(k<=tot+children[i].size) return children[i].query(k-tot);
				tot+=children[i].size;
			}
			return null;
		}
	}
}
