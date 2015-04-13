#pragma once

#include <echo/concept2.h>
#include <echo/expression_template/expression_template_traits.h>

namespace echo {
namespace expression_template {
namespace concept {

//////////////////////////////
// expression_template_node //
//////////////////////////////

namespace detail {
namespace concept {
struct ExpressionTemplateNode : Concept {
  template <class T>
  auto require(T&& node) -> list<
      valid<expression_template_traits::expression_template_tag<T>>(),
      valid<decltype(make_expression(
          expression_template_traits::expression_template_tag<T>(), node))>()>;
};
}
}

template <class T>
constexpr bool expression_template_node() {
  return models<detail::concept::ExpressionTemplateNode, T>();
}
}
}
}
