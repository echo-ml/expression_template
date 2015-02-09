#include <echo/expression_template/expression_template_assignment.h>
#include <echo/expression_template/arithmetic.h>
#include <catch.hpp>
#include <array>

using namespace echo;
using namespace echo::expression_template;

namespace echo { namespace expression_template {

struct mytag {};

template<class Functor, class Lhs, class Rhs>
auto make_assignment_expression(mytag, Functor f, const Lhs& lhs, const Rhs& rhs) {
  return [=](int i) {
    return f(lhs(i), rhs(i));
  };
}

template<class Functor, class Lhs, class Rhs>
auto make_binary_arithmetic_expression(mytag, Functor f, const Lhs& lhs, const Rhs& rhs) 
{
  return [=](int i) {
    return f(lhs(i), rhs(i));
  };
}

template<class Node>
auto make_expression(mytag, Node n) {
  return n;
}

auto make_expression(mytag, double x) {
  return [=](int i) {
    return x;
  };
}

struct Node : ExpressionTemplateAssignment<Node, mytag, double>
{
  double operator()(int i) const {
    return i;
  }
};

}} //end namespace echo::expression_template


TEST_CASE("arithmetic") {
  Node n1, n2;
  SECTION("add two nodes") {
    auto expr = n1 + n2;
    REQUIRE(expr(0) == 0);
    REQUIRE(expr(1) == 2);
    REQUIRE(expr(2) == 4);
  }
  SECTION("add node and scalar") {
    auto expr = n1 + 1.0;
    REQUIRE(expr(0) == 1);
    REQUIRE(expr(1) == 2);
    REQUIRE(expr(2) == 3);
  }
}
