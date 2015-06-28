#pragma once

#include <echo/expression_template/concept.h>

namespace echo {
namespace expression_template {

template <class Functor, class... Nodes,
          CONCEPT_REQUIRES(or_c<concept::node<Nodes>()...>() &&
                           concept::mappable<Functor, Nodes...>())>
auto map(Functor functor, const Nodes&... nodes) {
  auto expression_template_tag =
      expression_template_traits::first_expression_template_tag<Nodes...>();
  return make_map_expression(
      expression_template_tag, functor,
      make_expression(expression_template_tag, nodes)...);
}
}
}  // end namespace echo::expression_template

