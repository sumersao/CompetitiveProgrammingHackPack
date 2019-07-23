import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

public class ConvexHull {
	public static Stack<p> hull;
	public static p [] h;
	public static void main(String[] args) {
		Scanner in= new Scanner(System.in);
		int n= in.nextInt();
		p [] points = new p[n];
		for (int i = 0; i < n; i++) {
			points[i]= new p(in.nextInt(), in.nextInt());
		}
		hull= new Stack<>();
		int refIndex = getIndexMin(points, n);
		p.refX = points[refIndex].x;
		p.refY = points[refIndex].y;
		
		grahamScan(points, n);
		p [] h= new p[hull.size()];
		for (int i = 0; i < h.length; i++) {
			h[i]= hull.pop();
		}
		
		System.out.println(getarea(h));
	}
	//find starting point (bottom left)
	public static int getIndexMin(p[] ps, int n) {
		int res = 0;
		for (int i=1; i<n; i++)
			if (ps[i].y < ps[res].y || (ps[i].y == ps[res].y && ps[i].x < ps[res].x))
				res = i;
		return res;
	}
	//computes convex hull
	public static void grahamScan(p[] ps, int n) {
		Arrays.sort(ps);
		hull.push(ps[0]);
		hull.push(ps[1]);

		for (int i=2; i<n; i++) {
			p cur = ps[i];
			p mid = hull.pop();
			p prev = hull.pop();
			while (!prev.isRightTurn(mid, cur)) {
				mid = prev;
				prev = hull.pop();
			}

			hull.push(prev);
			hull.push(mid);
			hull.push(cur);
		}
	}
	//returns area of a polygon
	public static double getarea(p [] a) {
		long res=0;
		for (int i = 0; i < a.length; i++) {
			res+= ((a[i].x*a[(i+1)%a.length].y)-(a[(i+1)%a.length].x*a[i].y));
		}
		return res;
	}
}
class p implements Comparable<p> {
	public static int refX, refY;
	public int x, y;
	public p(int myx, int myy) {
		x = myx;
		y = myy;
	}
	public p getVect(p other) {
		return new p(other.x-x, other.y-y);
	}
	public double dist(p other) {
		return Math.sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
	}
	public double mag(p a) {
		return Math.sqrt(a.x*a.x+a.y*a.y);
	}
	public int crossProductMag(p other) {
		return this.x*other.y - other.x*this.y;
	}
	public boolean isRightTurn(p mid, p next) {
		p v1 = getVect(mid);
		p v2 = mid.getVect(next);
		return v1.crossProductMag(v2) >= 0;
	}
	public boolean isZero() {
		return x == 0 && y == 0;
	}
	public int compareTo(p other) {
		p myRef = new p(refX, refY);
		p v1 = myRef.getVect(this);
		p v2 = myRef.getVect(other);

		if (v1.isZero()) return -1;
		if (v2.isZero()) return 1;

		if (v1.crossProductMag(v2) != 0)
			return -v1.crossProductMag(v2);

		if (myRef.dist(v1) < myRef.dist(v2)) return -1;
		return 1;
	}
}