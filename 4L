#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <vector>
const double eps = 0.00001;

struct Point {
  long long x, y;
  Point(long long x = 0, long long y = 0) : x(x), y(y) {}
  Point(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {}
  Point operator+=(const Point& other);
  Point operator-=(const Point& other);
  Point operator*=(long long coefficient);
};

Point Point::operator+=(const Point& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Point Point::operator-=(const Point& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Point operator-(const Point& first, const Point& second) {
  Point answer;
  answer.x = first.x - second.x;
  answer.y = first.y - second.y;
  return answer;
}

Point Point::operator*=(long long coefficient) {
  x *= coefficient;
  y *= coefficient;
  return *this;
}

long long vectorMultiplication(const Point& first, const Point& second) {
  return first.x * second.y - first.y * second.x;
}

bool operator<=(const Point& u, const Point& v) {
  if ((u.y >= 0) != (v.y >= 0)) return u.y >= 0;
  double cos_u = 1.0 * u.x / std::sqrt(u.x * u.x + u.y * u.y);
  double cos_v = 1.0 * v.x / std::sqrt(v.x * v.x + v.y * v.y);
  if (u.y >= 0) {
    return ((cos_v - cos_u) < eps);
  }
  return ((cos_u - cos_v) < eps);
}

bool operator<(const Point& a, const Point& b) {
  return (a.x * b.y - a.y * b.x) > 0;
};

struct Polygon {
  std::vector<Point> vertices;

 public:
  Polygon() = default;
  Polygon(const std::vector<Point> vertices) : vertices(vertices) {}
  void read_counterclockwise();
  size_t size() const;
  int find_first_index() const;
  bool is_inside_convex_linear(const Point& p) const;
  int find_leftmost() const;
  Polygon moved() const;
  std::set<std::pair<Point, int>> sorted_vertices() const;
  bool contains(Point& church,
                const std::set<std::pair<Point, int>>& sorted_vertices) const;
  friend Polygon minkowski(const std::vector<Polygon>& polygons);
};

std::set<std::pair<Point, int>> Polygon::sorted_vertices() const {
  std::set<std::pair<Point, int>> vertex_set;
  for (int i = 1; i < size(); ++i) {
    vertex_set.insert({vertices[i], i});
  }
  return vertex_set;
}

int Polygon::find_leftmost() const {
  int zero = 0;
  for (int i = 0; i < size(); ++i) {
    if (vertices[i].x < vertices[zero].x)
      zero = i;
    else if (vertices[i].x == vertices[zero].x) {
      if (vertices[i].y < vertices[zero].y) zero = i;
    }
  }
  return zero;
}

Polygon Polygon::moved() const {
  int zero = find_leftmost();

  Polygon best;
  best.vertices.resize(size());
  for (int i = 0; i < size(); ++i) {
    best.vertices[i] = vertices[(zero + i) % size()] - vertices[zero];
  }
  return best;
}

size_t Polygon::size() const { return vertices.size(); }

void Polygon::read_counterclockwise() {
  int n;
  std::cin >> n;
  vertices.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vertices[i].x >> vertices[i].y;
  }
  Point p1(vertices[1], vertices[0]);
  Point p2(vertices[2], vertices[1]);
  if (p2 < p1) {
    std::reverse(vertices.begin(), vertices.end());
  }
}

int Polygon::find_first_index() const {
  int sz = size();
  int first_index = 1;
  bool previous_higher =
      vertices[(first_index - 1) % sz].y > vertices[first_index % sz].y;
  bool next_higher =
      vertices[first_index % sz].y <= vertices[(first_index + 1) % sz].y;
  while (!(previous_higher && next_higher)) {
    ++first_index;
    previous_higher =
        vertices[(first_index - 1) % sz].y > vertices[first_index % sz].y;
    next_higher =
        vertices[first_index % sz].y <= vertices[(first_index + 1) % sz].y;
  }
  first_index %= sz;
  return first_index;
}

std::vector<int> first_ind(const std::vector<Polygon>& polygons) {
  std::vector<int> first_index(polygons.size());

  for (int i = 0; i < polygons.size(); ++i) {
    first_index[i] = polygons[i].find_first_index();
  }

  return first_index;
}

size_t total_vertices(const std::vector<Polygon>& polygons) {
  size_t vertex_number = 0;
  for (const auto& polygon : polygons) {
    vertex_number += polygon.size();
  }
  return vertex_number;
}

Point leftmost(const std::vector<Polygon>& polygons,
               const std::vector<int>& first_index) {
  Point answer;
  for (int i = 0; i < polygons.size(); ++i) {
    answer += polygons[i].vertices[first_index[i]];
  }
  return answer;
}

std::vector<Point> first_points(const std::vector<Polygon>& polygons,
                                const std::vector<int>& first_index) {
  std::vector<Point> points(polygons.size());
  for (int i = 0; i < polygons.size(); ++i) {
    int sz = polygons[i].size();
    Point left_end = polygons[i].vertices[(first_index[i]) % sz];
    Point right_end = polygons[i].vertices[(first_index[i] + 1) % sz];
    points[i] = Point(left_end, right_end);
  }
  return points;
}

bool is_best_point(const std::vector<Polygon>& polygons, int i,
                   const std::vector<Point>& current_point,
                   const std::vector<int>& current_index) {
  for (int j = 0; j < polygons.size(); ++j) {
    if (i != j && !(current_point[i] <= current_point[j]) &&
        current_index[j] != polygons[j].size()) {
      return false;
    }
  }
  return true;
}

Polygon minkowski(const std::vector<Polygon>& polygons) {
  Polygon answer;
  std::vector<int> first_index = first_ind(polygons);
  size_t vertex_number = total_vertices(polygons);

  answer.vertices.resize(vertex_number);
  answer.vertices[0] = leftmost(polygons, first_index);

  std::vector<int> current_index(polygons.size(), 0);
  std::vector<Point> current_point = first_points(polygons, first_index);

  for (int vertex = 1; vertex < vertex_number; ++vertex) {
    for (int i = 0; i < polygons.size(); ++i) {
      bool is_best = is_best_point(polygons, i, current_point, current_index);
      if (current_index[i] < polygons[i].size() && is_best) {
        answer.vertices[vertex] = answer.vertices[vertex - 1];
        answer.vertices[vertex] += current_point[i];
        ++current_index[i];
        size_t sz = polygons[i].size();
        Point left_end =
            polygons[i].vertices[(first_index[i] + current_index[i]) % sz];
        Point right_end =
            polygons[i].vertices[(first_index[i] + current_index[i] + 1) % sz];
        current_point[i] = Point(left_end, right_end);
        break;
      }
    }
  }
  return answer;
}

bool Polygon::is_inside_convex_linear(const Point& p) const {
  std::vector<Point> point_2_vertex(size());
  for (int i = 0; i < size(); ++i) {
    point_2_vertex[i] = vertices[i] - p;
  }

  std::vector<long long> multiplications(size());
  for (int i = 0; i < size(); ++i) {
    multiplications[i] = vectorMultiplication(point_2_vertex[i],
                                              point_2_vertex[(i + 1) % size()]);
  }

  bool all_not_less = true;
  bool all_not_greater = true;

  for (const auto& multi : multiplications) {
    if (multi < 0) {
      all_not_less = false;
    }
    if (multi > 0) {
      all_not_greater = false;
    }
  }
  return (all_not_less || all_not_greater);
}

void rearrange_church(Point& church, int cities_num, Point zero) {
  church *= cities_num;
  church -= zero;
}

bool Polygon::contains(
    Point& church,
    const std::set<std::pair<Point, int>>& sorted_vertices) const {
  if (church.x == 0 && church.y == 0) {
    return true;
  }
  if (church.x < 0 || church < vertices[1] || (vertices.back() < church)) {
    return false;
  }

  auto previous = sorted_vertices.lower_bound({church, -1});
  if (previous == sorted_vertices.begin()) {
    auto next = sorted_vertices.upper_bound({church, INT_MAX});
    --next;
    return (church.x <= vertices[next->second].x);
  }
  Polygon triangle({vertices[0], vertices[previous->second],
                    vertices[previous->second - 1]});
  return triangle.is_inside_convex_linear(church);
}

int main() {
  int city_num = 3;
  std::vector<Polygon> cities(city_num);
  for (int i = 0; i < city_num; ++i) {
    cities[i].read_counterclockwise();
  }

  Polygon cities_sum = minkowski(cities);
  Polygon cities_centered = cities_sum.moved();
  std::set<std::pair<Point, int>> sorted_vertices =
      cities_centered.sorted_vertices();
  Point zero = cities_sum.vertices[cities_sum.find_leftmost()];

  int q;
  std::cin >> q;
  Point church;
  for (int i = 0; i < q; ++i) {
    std::cin >> church.x >> church.y;
    rearrange_church(church, city_num, zero);
    std::cout << ((cities_centered.contains(church, sorted_vertices)) ? "YES" : "NO") << '\n';
  }
}
