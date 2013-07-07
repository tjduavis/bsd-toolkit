/*
 * Workshop 9
 * Abstract Base Classes
 * Polygon.h
 * Timothy Duavis
 */
 
 #define SHAPE_SIZE 30
 #include <string.h>
 #include <iostream>
 
 class Showable {
	 virtual ostream& display(ostream& os) const = 0;
	 friend ostream& operator<<(ostream& showOut, Showable& src) {
		 return src.display(showOut);
	 }
 };
 
 class Point : virtual Showable {
	 float xPt;
	 float yPt;
	 public:
	 Point() : xPt(0.0), yPt(0.0) { }
	 Point(float x, float y) : xPt(x), yPt(y) { }
	 Point(Point& src) {
		 xPt = src.xPt;
		 yPt = src.yPt;
	 }
	 ostream& display(ostream& os) const {
		 os.setf(ios::fixed);
		 os.precision(1);
		 os << "Centriod (" << xPt << ',' << yPt << ')';
		 return os;
	 }
	 Point& operator=(const Point& rhs) {
		 if (this != &rhs) {
			 xPt = rhs.xPt;
		 	 yPt = rhs.yPt;
	 	 }
	 	 return *this;
 	 }
	 friend Point& operator+(const Point& a, const Point& b) {
		 Point temp;
		 temp.xPt = a.xPt + b.xPt;
		 temp.yPt = a.yPt + b.yPt;
		 
		 return temp;
	 }
	 friend Point& operator+=(Point& ls, Point& rs) {
		 ls.xPt += rs.xPt;
		 ls.yPt += rs.yPt;
		 
		 return ls;
	 }
	 friend Point& operator/(const Point& a, int divisor) {
		 Point temp;
		 temp.xPt = a.xPt / divisor;
		 temp.yPt = a.yPt / divisor;
		 
		 return temp;
	 }
 };
 
 class Shape : virtual public Showable {
	 char type[SHAPE_SIZE + 1];
	 protected:
	 ostream& display(ostream& os) const { 
		 os << type << ' ';
		 return os;
	 }
	 public:
	 Shape(char* shpName) {
		 strcpy(type,shpName);
	 }
	 virtual Point centroid() const = 0;
 };
 
 class Polygon : public Shape {
	 Point* vertex;
	 int vertices;
	 char pname[SHAPE_SIZE + 1];
	 void init(Polygon& src) {
		 vertices = src.vertices;
		 vertex = new Point[vertices];
		 strcpy(pname,src.pname);
		 for (int i = 0; i < vertices; i++) vertex[i] = src.vertex[i];
	 }
	 public:
	 Polygon(char* name, int descp) : Shape(name), vertices(descp) {
		 vertex = new Point [vertices];
		 strcpy(pname,name);
	 }
	 Polygon(Polygon& src) : Shape(src.pname) {
		 init(src);
	 }
	 ~Polygon() { if (vertex) delete [] vertex; }
	 Point centroid() const {
		Point sum,append;
		for (int i = 0; i < vertices; i++) {
			if (i+1 < vertices)
				sum = vertex[i] + vertex[++i];
			else 
				sum = vertex[i] + vertex[i-1];
			append += sum;
	 	}
		append = append / vertices;
	 	return append;
 	 }
	 ostream& display(ostream& os) const {
		 Point sol = centroid();
		 Shape::display(os);
		 return sol.display(os);
	 }
	 Point& operator()(int i) {
		 return vertex[i];
	 }
	 Polygon& operator=(Polygon& rhs) {
	 	 if (this != &rhs) {
	 		 if (vertex) delete [] vertex;
	 		 init(rhs);
	 	 }
	 	 return *this;
	 }
 };