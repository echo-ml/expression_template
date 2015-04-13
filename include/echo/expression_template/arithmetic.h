#pragma once

#include <echo/expression_template/concept.h>
#include <echo/enable_if.h>
#include <echo/expression_template/map.h>

namespace echo {
namespace expression_template {

#define ECHO_BINARY_ARITHMETIC(SYMBOL, NAME, LOWER_NAME)                     \
  struct NAME##ArithmeticFunctor {                                           \
    template <class Lhs, class Rhs>                                          \
    auto operator()(const Lhs& lhs, const Rhs& rhs) const                    \
        -> decltype(lhs + rhs) {                                             \
      return lhs SYMBOL rhs;                                                 \
    }                                                                        \
  };                                                                         \
  template <                                                                 \
      class Lhs, class Rhs,                                                  \
      CONCEPT_REQUIRES(                                                      \
          concept::expression_template_node<Lhs>() &&                        \
          concept::expression_template_node<Rhs>() &&                        \
          std::is_same<                                                      \
              expression_template_traits::expression_template_tag<Lhs>,      \
              expression_template_traits::expression_template_tag<Rhs> >())> \
  auto operator SYMBOL(const Lhs& lhs, const Rhs& rhs) {                     \
    typename Lhs::expression_template_tag expression_template_tag;           \
    return make_binary_arithmetic_expression(                                \
        expression_template_tag, NAME##ArithmeticFunctor(),                  \
        make_expression(expression_template_tag, lhs),                       \
        make_expression(expression_template_tag, rhs));                      \
  }                                                                          \
  template <class Lhs, class Rhs,                                            \
            CONCEPT_REQUIRES(concept::expression_template_node<Lhs>() &&     \
                             !concept::expression_template_node<Rhs>())>     \
  auto operator SYMBOL(const Lhs& lhs, const Rhs& rhs) {                     \
    typename Lhs::expression_template_tag expression_template_tag;           \
    return make_binary_arithmetic_expression(                                \
        expression_template_tag, NAME##ArithmeticFunctor(),                  \
        make_expression(expression_template_tag, lhs),                       \
        make_expression(expression_template_tag, rhs));                      \
  }                                                                          \
  template <class Lhs, class Rhs,                                            \
            CONCEPT_REQUIRES(!concept::expression_template_node<Lhs>() &&    \
                             concept::expression_template_node<Rhs>())>      \
  auto operator SYMBOL(const Lhs& lhs, const Rhs& rhs) {                     \
    typename Rhs::expression_template_tag expression_template_tag;           \
    return make_binary_arithmetic_expression(                                \
        expression_template_tag, NAME##ArithmeticFunctor(),                  \
        make_expression(expression_template_tag, lhs),                       \
        make_expression(expression_template_tag, rhs));                      \
  }
#include <echo/expression_template/binary_arithmetic-def.h>
#undef ECHO_BINARY_ARITHMETIC

#define ECHO_UNARY_ARITHMETIC(SYMBOL, NAME, LOWER_NAME)                     \
  struct NAME##ArithmeticFunctor {                                          \
    template <class Operand>                                                \
    auto operator()(const Operand& operand) const -> decltype(-operand) {   \
      return SYMBOL operand;                                                \
    }                                                                       \
  };                                                                        \
  template <class Operand,                                                  \
            CONCEPT_REQUIRES(concept::expression_template_node<Operand>())> \
  auto operator SYMBOL(const Operand& operand) {                            \
    return map(NAME##ArithmeticFunctor(), operand);                         \
  }
#include <echo/expression_template/unary_arithmetic-def.h>
#undef ECHO_UNARY_ARITHMETIC
}
}  // end namespace echo::expression_template
