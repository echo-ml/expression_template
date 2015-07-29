#pragma once

#include <echo/expression_template/concept.h>
#include <echo/utility/functional.h>

namespace echo {
namespace expression_template {

//------------------------------------------------------------------------------
// reduce
//------------------------------------------------------------------------------
template <class Identity, class Reducer, class Node,
          CONCEPT_REQUIRES(concept::reducible<Identity, Reducer, Node>())>
auto reduce(const Identity& identity, const Reducer& reducer,
            const Node& node) {
  auto expression_template_tag =
      expression_template_traits::expression_template_tag<Node>();
  return make_reduction_expression(
      expression_template_tag, identity, reducer,
      make_expression(expression_template_tag, node));
}

//------------------------------------------------------------------------------
// sum_elements
//------------------------------------------------------------------------------
template <class Node, CONCEPT_REQUIRES(concept::reducible<
                          int, uncvref_t<decltype(functional::plus)>, Node>())>
auto sum_elements(const Node& node) {
  return reduce(0, functional::plus, node);
}
}
}
