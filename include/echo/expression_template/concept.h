#pragma once

#include <echo/concept2.h>
#include <echo/expression_template/expression_template_traits.h>
#include <echo/execution_context.h>

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

//////////
// node //
//////////

template <class T>
constexpr bool node() {
  return expression_template_node<T>() ||
         execution_context::concept::scalar<T>();
}

//////////////////////
// compatible_nodes //
//////////////////////

namespace detail {
namespace concept {

template <class ExpressionTemplateTag, class Node,
          CONCEPT_REQUIRES(expression_template_node<Node>())>
auto compatible_node_impl(Node && )
    -> std::is_same<ExpressionTemplateTag,
                    expression_template_traits::expression_template_tag<Node>>;

template <class ExpressionTemplateTag, class Node,
          CONCEPT_REQUIRES(execution_context::concept::scalar<Node>())>
auto compatible_node_impl(Node && ) -> std::true_type;

template <class ExpressionTemplateTag>
auto compatible_node_impl(...) -> std::false_type;

template <class ExpressionTemplateTag, class Node>
constexpr bool compatible_node() {
  using Result = decltype(
      compatible_node_impl<ExpressionTemplateTag>(std::declval<Node>()));
  return Result::value;
}

struct CompatibleNodes : Concept {
  template <class... Nodes>
  auto require(Nodes&&...) -> list<const_algorithm::and_c<compatible_node<
      expression_template_traits::first_expression_template_tag<Nodes...>,
      Nodes>()...>()>;
};
}
}

template <class... Nodes>
constexpr bool compatible_nodes() {
  return models<detail::concept::CompatibleNodes, Nodes...>();
}

//////////////
// mappable //
//////////////

namespace detail {
namespace concept {
struct Mappable : Concept {
  template <class Functor, class... Nodes>
  auto require(Functor&& functor, Nodes&&... nodes) -> list<
      compatible_nodes<Nodes...>(),
      expression_template_node<decltype(make_map_expression(
          expression_template_traits::first_expression_template_tag<Nodes...>(),
          functor,
          make_expression(expression_template_traits::
                              first_expression_template_tag<Nodes...>(),
                          nodes)...))>()>;
};
}
}

template <class Functor, class... Nodes>
constexpr bool mappable() {
  return models<detail::concept::Mappable, Functor, Nodes...>();
}
}
}
}
