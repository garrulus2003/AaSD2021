#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  long long x;
  long long y;

  Point(long long X = 0, long long Y = 0) : x(X), y(Y) {}
  long long length() const;
  Point operator+=(const Point& other);
};

Point operator-(const Point& v1, const Point& v2) {
  return Point(v1.x - v2.x, v1.y - v2.y);
}

Point Point::operator+=(const Point& other) {
  x += other.x;
  y += other.y;
  return *this;
}

long long vectorMultiplication(const Point& v1, const Point& v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

long long Point::length() const { return x * x + y * y; };

bool angle_comp(const Point& p, const Point& q) {
  return (vectorMultiplication(p, q) > 0 ||
          (vectorMultiplication(p, q) == 0 && p.length() < q.length()));
}

class Polygon {
  std::vector<Point> vertices;

 public:
  Polygon convex_hull() const;
  void read(int size);
  void print() const;
  size_t size() const;
};

Polygon Polygon::convex_hull() const {
  int n = vertices.size();

  Point start = vertices[0];

  for (size_t i = 0; i < n; ++i) {
    if (vertices[i].x < start.x ||
        (vertices[i].x == start.x && vertices[i].y < start.y)) {
      start = vertices[i];
    }
  }

  Polygon copy(*this);

  for (size_t i = 0; i < n; ++i) {
    copy.vertices[i] = copy.vertices[i] - start;
  }

  std::sort(copy.vertices.begin(), copy.vertices.end(), angle_comp);
  Polygon convex_hull;

  for (size_t i = 0; i < n; ++i) {
    while (convex_hull.size() > 1) {
      Point new_side = (copy.vertices[i] - convex_hull.vertices.back());
      Point last_side = convex_hull.vertices[convex_hull.size() - 2] -
                        convex_hull.vertices.back();
      if (vectorMultiplication(new_side, last_side) <= 0) {
        convex_hull.vertices.pop_back();
        continue;
      }
      break;
    }
    convex_hull.vertices.push_back(copy.vertices[i]);
  }
  for (auto& vertex : convex_hull.vertices) {
    vertex += start;
  }
  return convex_hull;
}

void Polygon::read(int size) {
  vertices.resize(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> vertices[i].x >> vertices[i].y;
  }
}

void Polygon::print() const {
  for (int i = 0; i < vertices.size(); ++i) {
    std::cout << vertices[i].x << " " << vertices[i].y << '\n';
  }
}

size_t Polygon::size() const { return vertices.size(); }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  Polygon polygon;
  int n;
  std::cin >> n;
  polygon.read(n);
  Polygon convex_hull = polygon.convex_hull();
  std::cout << convex_hull.size() << '\n';
  convex_hull.print();
  return 0;
}
