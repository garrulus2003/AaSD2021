#include <algorithm>

#include <cmath>

#include <iomanip>

#include <iostream>

#include <vector>

const double EPS = 1e-10;

//Comparison functions

bool equal(double a, double b) {
  return std::fabs(a - b) < EPS;
}

bool leq(double a, double b) {
  return (b - a) > -EPS;
}

bool geq(double a, double b) {
  return (a - b) > -EPS;
}

//Elementary geometric objects

struct Point;
struct Vector;
struct Segment;
class Line;

struct Point {
  double x;
  double y;

  Point(double X, double Y): x(X), y(Y) {}
  Point(): x(0.0), y(0.0) {}
  Point(Line l1, Line l2);
};

bool operator == (const Point & a,
  const Point & b) {
  return equal(a.x, b.x) && equal(a.y, b.y);
}

bool operator != (const Point & a,
  const Point & b) {
  return !(a == b);
}

struct Vector: public Point {
  Vector() =
    default;
  Vector(double a, double b): Point(a, b) {}
  Vector(const Point & end,
    const Point & begin): Point(begin.x - end.x, begin.y - end.y) {}
};

Vector operator + (const Vector & v1,
  const Vector & v2) {
  return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator - (const Vector & v1,
  const Vector & v2) {
  return Vector(v1.x - v2.x, v1.y - v2.y);
}

class Line {
  public:
    double a;
  double b;
  double c;

  Line(): a(1), b(0), c(0) {}
  Line(double A, double B, double C): a(A), b(B), c(C) {}
  Line(const Point & p1,
    const Point & p2);

  bool operator == (const Line & other) const;
  bool operator != (const Line & other) const;
};

bool Line::operator == (const Line & other) const {
  return equal(a * other.b, b * other.a) && equal(b * other.c, c * other.b) && equal(c * other.a, a * other.c);
}

bool Line::operator != (const Line & other) const {
  return !( * this == other);
}

Line::Line(const Point & p1,
  const Point & p2) {
  a = p1.y - p2.y;
  b = p2.x - p1.x;
  c = p2.y * p1.x - p2.x * p1.y;
}

//Elementary geometry functions

bool parallel(const Line & line1,
  const Line & line2) {
  return equal(0.0, line1.a * line2.b - line1.b * line2.a);
}

bool incident(const Point & point,
  const Line & line) {
  return equal(0.0, line.a * point.x + line.b * point.y + line.c);
}

//Point as the intersection of two lines

Point::Point(Line l1, Line l2) {
  double det = l1.a * l2.b - l2.a * l1.b;
  if (equal(det, 0)) {
    Point();
  }
  double det1 = -(l1.c * l2.b - l2.c * l1.b);
  double det2 = -(l1.a * l2.c - l2.a * l1.c);
  x = det1 / det;
  y = det2 / det;
}

struct Segment: Vector {
  Point start;
  Point finish;
  Segment(Point s, Point f): start(s), finish(f), Vector(s, f) {}
};

bool is_between(const Segment & s,
  const Point & p) {
  Point finish(s.finish);
  bool x_between = (leq(s.start.x, p.x) && geq(finish.x, p.x)) || (geq(s.start.x, p.x) && leq(finish.x, p.x));
  bool y_between = (leq(s.start.y, p.y) && geq(finish.y, p.y)) || (geq(s.start.y, p.y) && leq(finish.y, p.y));
  return x_between && y_between;
}

class Polygon {
  public:
    Polygon(): vertices(std::vector < Point > (0)) {}
  explicit Polygon(std::vector < Point > & points): vertices(points) {} //constructor from a vector of vertices

  bool containsPoint(Point point) const;

  private:
    std::vector < Point > vertices;
};

bool Polygon::containsPoint(Point point) const {
  for (int i = 0; i < vertices.size(); ++i) {
    Segment current_side(vertices[i], vertices[(i + 1) % vertices.size()]);
    Line current_line(vertices[i], vertices[(i + 1) % vertices.size()]);
    if (is_between(current_side, point) && incident(point, current_line)) {
      return true;
    }
  }

  int intersections = 0;
  Line secant(0, 1, -point.y);

  for (int i = 0; i < vertices.size(); ++i) {
    Line current_line(vertices[i], vertices[(i + 1) % vertices.size()]);
    Segment current_side(vertices[i], vertices[(i + 1) % vertices.size()]);
    if (parallel(secant, current_line)) continue;
    Point p(secant, current_line);
    if (is_between(current_side, p) && geq(p.x, point.x)) {
      if (p != vertices[i] && p != vertices[(i + 1) % vertices.size()]) {
        ++intersections;
        continue;
      }
      if (p == vertices[(i + 1) % vertices.size()]) {
        if ((vertices[i].y >= p.y) ^ (vertices[(i + 2) % vertices.size()].y >= p.y)) {
          ++intersections;
        }
      }
    }
  }
  return (intersections % 2 == 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  double x, y;
  std::cin >> n;
  std::cin >> x >> y;
  Point point(x, y);

  std::vector < Point > vertices(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    vertices[i].x = x;
    vertices[i].y = y;
  }

  Polygon polygon(vertices);
  std::cout << (polygon.containsPoint(point) ? "YES" : "NO");
}
