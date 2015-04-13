#pragma once

namespace echo {
namespace expression_template_traits {

template <class ExpressionTemplateNode>
using expression_template_tag =
    typename ExpressionTemplateNode::expression_template_tag;
}
}
