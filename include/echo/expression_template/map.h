#pragma once

#include <echo/expression_template/expression.h>
#include <echo/const_algorithm.h>

namespace echo { namespace expression_template {

namespace detail {

template<
    class NodeFirst
  , class... NodesRest
  , enable_if<is_expression_template_node<NodeFirst>> = 0
>
auto get_expression_template_tag(const NodeFirst&, const NodesRest&...) {
  return typename NodeFirst::expression_template_tag();
}

template<
    class NodeFirst
  , class... NodesRest
  , disable_if<is_expression_template_node<NodeFirst>> = 0
>
auto get_expression_template_tag(const NodeFirst&, const NodesRest&... nodes_rest) {
  return get_expression_template_impl(nodes_rest...);
}

} //end namespace detail

template<
    class Functor
  , class... Nodes
  , enable_if_c<
      const_algorithm::or_(
          fatal::constant_sequence<bool, is_expression_template_node<Nodes>::value...>()
      )
    > = 0
>
auto map(Functor functor, const Nodes&... nodes) {
  auto expression_template_tag = detail::get_expression_template_tag(nodes...);
  return make_map_expression(expression_template_tag
                           , functor
                           , make_expression(expression_template_tag, nodes)...);
}

}} //end namespace echo::expression_template

