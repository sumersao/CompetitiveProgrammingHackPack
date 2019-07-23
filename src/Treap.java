import java.util.Random;

public class Treap {
	public static Random rand= new Random();
	static class Node{
		int key, pri, sub;
		Node l, r;
		public Node(int k) {
			key= k;
			pri = rand.nextInt();
			sub= 1;
			l=null;
			r= null;
		}
		public int gsub(Node t) {
			if(t==null) return 0;
			return t.sub;
		}
		public pair split(Node t, int k) {
			if(t==null) {
				Node l= null;
				Node r= null;
				pair ret= new pair(l, r);
				return ret;
			}
			if(t.key<=k) {
				pair got= split(t.r ,k);
				t.r= got.l;
				pair ret= new pair(t, got.r);
				return ret;
			}
			else {
				pair got= split(t.l, k);
				t.l = got.r;
				pair ret= new pair(got.l, t);
				return ret;
			}
		}
		public Node merge(Node l, Node r) {
			if(l==null&&r==null) return null;
			else if(l==null) return r;
			else if(r==null) return l;
			else if(l.pri > r.pri){
				Node got= merge(l.r, r);
				l.r= got;
				l.sub= 1+ gsub(l.l)+ gsub(l.r);
				return l;
			}
			else {
				Node got= merge(l, r.l);
				r.l= got;
				r.sub= 1+ gsub(r.l) + gsub(r.r);
				return r;
			}
		}
	}
	static class pair{
		Node l;
		Node r;
		public pair(Node a, Node b) {
			l=a;
			r=b;
		}
	}
}
