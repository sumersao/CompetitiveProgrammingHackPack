public class Geometry {
	//returns area of a polygon
	public static double getarea(p [] a) {
		long res=0;
		for (int i = 0; i < a.length; i++) {
			res+= ((a[i].x*a[(i+1)%a.length].y)-(a[(i+1)%a.length].x*a[i].y));
		}
		return res;
	}
	//dist= (|(p-a)x(b-a)|)/|b-a| 
	public static double pointlinedist(p pt, line l) {
		p ab= l.start.vec(l.end);
		p ap= pt.vec(l.start);
		double top= ab.cross(ap);
		double den= ab.mag();
		return top/den;
	}
	public static double pointsegdist(p pt, line l) {
		p ab= l.start.vec(l.end);
		p ap= pt.vec(l.start);
		p bp= pt.vec(l.end);
		double ang= ab.ang(ap);
		if(ang<Math.PI/2) {
			return pointlinedist(pt, l);
		}
		return Math.min(ap.mag(), bp.mag());
	}
	public static boolean sameside(p a, p b, line l) {
		p c= l.start;
		p d= l.end;
		p ab= a.vec(b);
		p ac= a.vec(c);
		p ad= a.vec(d);
		int c1= ab.cross(ac);
		int c2= ab.cross(ad);
		if((c1<0&&c2<0)||(c1>0&&c2>0)) return true;
		return false;
	}
	public static boolean segmentsintersect(line a, line b) {
		return sameside(a.start, a.end, b)&&sameside(b.start,b.end,a);
	}
	static class p{
		int x, y;
		public p(int a, int b) {
			x=a;
			y=b;
		}
		//vector from me to other
		public p vec(p other) {
			return new p(other.x-x, other.y-y);
		}
		public double dist(p other) {
			return Math.sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
		}
		public int cross(p other) {
			return this.x*other.y - other.x*this.y;
		}
		public double mag() {
			return Math.sqrt(x*x+y*y);
		}
		public double dot(p other) {
			return x*other.x+ y*other.y;
		}
		public double ang(p other) {
			double dot= dot(other);
			double dd= mag()*other.mag();
			return Math.acos(dot/dd);
		}
	}
	static class line{
		p start, end, dir;
		public line(p a, p b) {
			start= new p(a.x,a.y);
			end= new p(b.x, b.y);
			dir= start.vec(end);
		}
	}
}