#include <echo/expression_template/expression_template_assignment.h>
#include <catch.hpp>
#include <array>

using namespace echo;
using namespace echo::expression_template;

struct mytag {};

namespace echo { namespace expression_template {


template<class Functor, class Lhs, class Rhs>
auto make_assignment_expression(mytag, Functor f, const Lhs& lhs, const Rhs& rhs) {
  return [=](int i) {
    return f(lhs(i), rhs(i));
  };
}

template<class Node>
auto make_expression(mytag, Node n) {
  return n;
}

}} //end namespace echo::expression_template

struct Node1 : ExpressionTemplateConstAssignment<mytag, Node1>
{
  using ExpressionTemplateConstAssignment<mytag, Node1>::operator=;

  double& operator()(int i) const {
    return a[i];
  }
  double* a;
};

struct Node2 : ExpressionTemplateAssignment<mytag, Node2>
{
  double operator()(int i) const {
    return 2*i;
  }
};

TEST_CASE("expression_template_assignment") {
  double a[3];
  Node1 n1;
  n1.a = a;
  Node2 n2;

  SECTION("operator=") {
    auto expr = (n1 = n2);
    expr(0);
    expr(1);
    expr(2);
    REQUIRE(a[0] == 0);
    REQUIRE(a[1] == 2);
    REQUIRE(a[2] == 4);
  }
}