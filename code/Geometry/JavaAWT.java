import java.util.*;
import java.io.*;
import java.awt.geom.*;
import java.lang.*;
//Lazy Geometry
class AWT{
	static Area makeArea(double[] pts){
		Path2D.Double p = new Path2D.Double();
		p.moveTo(pts[0], pts[1]);
		for(int i = 2; i < pts.length; i+=2){
			p.lineTo(pts[i], pts[i+1]);
		}
		p.closePath();
		return new Area(p);
	}
	static double computePolygonArea(ArrayList<Point2D.Double> points) {
		Point2D.Double[] pts = points.toArray(new Point2D.Double[points.size()]);  
		double area = 0;
		for (int i = 0; i < pts.length; i++){
			int j = (i+1) % pts.length;
			area += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
		}        
		return Math.abs(area)/2;
	}
	static double computeArea(Area area) {
		double totArea = 0;
		PathIterator iter = area.getPathIterator(null);
		ArrayList<Point2D.Double> points = new ArrayList<Point2D.Double>();
		while (!iter.isDone()) {
			double[] buffer = new double[6];
			switch (iter.currentSegment(buffer)) {
				case PathIterator.SEG_MOVETO:
				case PathIterator.SEG_LINETO:
					points.add(new Point2D.Double(buffer[0], buffer[1]));
					break;
				case PathIterator.SEG_CLOSE:
					totArea += computePolygonArea(points);
					points.clear();
					break;
			}
			iter.next();
		}
		return totArea;
	}
}
