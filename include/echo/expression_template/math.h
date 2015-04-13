#pragma once

#include <cmath>

#include <echo/const_algorithm.h>
#include <echo/enable_if.h>
#include <echo/expression_template/map.h>
#include <echo/expression_template/concept.h>

namespace echo {
namespace expression_template {

#define ECHO_UNARY_MATH(FUNCTION, NAME, LOWER_NAME)                      \
  struct NAME##Functor {                                                 \
    template <class Scalar>                                              \
    auto operator()(Scalar x) const {                                    \
      return FUNCTION(x);                                                \
    }                                                                    \
  };                                                                     \
  template <class Node,                                                  \
            CONCEPT_REQUIRES(concept::expression_template_node<Node>())> \
  auto LOWER_NAME(const Node& node) {                                    \
    return map(NAME##Functor(), node);                                   \
  }
#include <echo/expression_template/unary_math-def.h>
#undef ECHO_UNARY_MATH
}
}  // end namespace echo::expression_template
