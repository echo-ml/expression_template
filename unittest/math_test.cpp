#include <echo/expression_template/arithmetic.h>
#include <echo/expression_template/math.h>
#include <catch.hpp>

using namespace echo;
using namespace echo::expression_template;

namespace echo { namespace expression_template {

struct mytag {};

template<class Node>
auto make_expression(mytag, Node n) {
  return n;
}

template<class Functor, class Node>
struct MapExpression {
  Functor f; Node node;
  using expression_template_tag = mytag;
  auto operator()(int i) {
    return f(node(i));
  }
};

template<class Functor, class Node>
auto make_expression(mytag, const MapExpression<Functor, Node>& e) {
  return e;
}

template<class Functor, class Node>
auto make_map_expression(mytag, Functor f, Node node) {
  return MapExpression<Functor, Node>{f, node};
}

struct Node 
{
  using expression_template_tag = mytag;

  double operator()(int i) const {
    return i;
  }
};

}} //end namespace echo::expression_template

TEST_CASE("math") {
  Node n1;
  SECTION("unary functions") {
    auto expr = sqrt(n1);
    REQUIRE(expr(0) == 0);
    REQUIRE(expr(1) == 1);
    REQUIRE(expr(2) == std::sqrt(2));
  }
  SECTION("negate") {
    auto expr = -n1;
    REQUIRE(expr(0) == 0);
    REQUIRE(expr(1) == -1);
  }
}
