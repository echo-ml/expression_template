#pragma once

#include <echo/concept2.h>

namespace echo {
namespace expression_template_traits {

/////////////////////////////
// expression_template_tag //
/////////////////////////////

template <class ExpressionTemplateNode>
using expression_template_tag =
    typename ExpressionTemplateNode::expression_template_tag;

///////////////////////////////////
// first_expression_template_tag //
///////////////////////////////////

namespace detail {
namespace expression_template_traits {
ECHO_MAKE_TYPE_QUERIER(expression_template_tag)
}
}

namespace detail {
namespace expression_template_traits {
template <bool, class...>
struct first_expression_template_tag_impl {};

template <class NodeFirst, class... NodesRest>
struct first_expression_template_tag_impl<true, NodeFirst, NodesRest...> {
  using type = typename NodeFirst::expression_template_tag;
};

template <class NodeFirst, class NodeSecond, class... NodesRest>
struct first_expression_template_tag_impl<false, NodeFirst, NodeSecond,
                                          NodesRest...>
    : first_expression_template_tag_impl<
          has_expression_template_tag<NodeSecond>(), NodeSecond, NodesRest...> {
};

template <class...>
struct first_expression_template_tag_impl2 {};

template <class NodeFirst, class... NodesRest>
struct first_expression_template_tag_impl2<NodeFirst, NodesRest...>
    : first_expression_template_tag_impl<
          has_expression_template_tag<NodeFirst>(), NodeFirst, NodesRest...> {};
}
}

template <class... Nodes>
using first_expression_template_tag =
    typename detail::expression_template_traits::
        first_expression_template_tag_impl2<Nodes...>::type;
}
}
