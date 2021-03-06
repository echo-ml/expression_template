#include <echo/expression_template/expression_template_assignment.h>
#include <catch.hpp>
#include <array>

using namespace echo;
using namespace echo::expression_template;

struct mytag {};

namespace echo {
namespace expression_template {

template <class Evaluator>
struct AssignmentExpression
    : ExpressionTemplateConstAssignment<AssignmentExpression<Evaluator>, mytag,
                                        double> {
  AssignmentExpression(const Evaluator& evaluator) : _evaluator(evaluator) {}
  using structure = execution_context::structure::general;
  auto dimensionality() const { return DimensionalityC<3>(); }
  const auto& evaluator() const { return _evaluator; }
  Evaluator _evaluator;
};

template <class Evaluator>
auto make_assignment_expression(Evaluator evaluator) {
  return AssignmentExpression<Evaluator>(evaluator);
}

template <class Functor, class Lhs, class Rhs>
auto make_assignment_expression(mytag, Functor f, const Lhs& lhs,
                                const Rhs& rhs) {
  return make_assignment_expression([=](int i) { return f(lhs(i), rhs(i)); });
}

template <class Functor, class Lhs, class Rhs>
struct MapExpression {
  using expression_template_tag = mytag;
  Functor f;
  Lhs lhs;
  Rhs rhs;
};

template <class Functor, class Lhs, class Rhs>
auto make_map_expression(mytag, Functor f, const Lhs& lhs, const Rhs& rhs) {
  return MapExpression<Functor, Lhs, Rhs>{f, lhs, rhs};
}

template <class Node>
auto make_expression(mytag, Node n) {
  return n;
}
}
}  // end namespace echo::expression_template

struct Node1 : ExpressionTemplateConstAssignment<Node1, mytag, double> {
  using ExpressionTemplateConstAssignment<Node1, mytag, double>::operator=;

  auto dimensionality() const { return DimensionalityC<3>(); }
  const auto& evaluator() const { return *this; }

  double& operator()(int i) const { return a[i]; }
  double* a;
};

struct Node2 : ExpressionTemplateConstAssignment<Node2, mytag, double> {
  auto dimensionality() const { return DimensionalityC<3>(); }

  const auto& evaluator() const { return *this; }
  double operator()(int i) const { return 2 * i; }
};

TEST_CASE("expression_template_assignment") {
  double a[3];
  Node1 n1;
  n1.a = a;
  Node2 n2;

  SECTION("operator=") {
    auto expr = (n1 = n2);
    expr.evaluator()(0);
    expr.evaluator()(1);
    expr.evaluator()(2);
    REQUIRE(a[0] == 0);
    REQUIRE(a[1] == 2);
    REQUIRE(a[2] == 4);
  }
}
