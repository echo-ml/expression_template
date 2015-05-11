#pragma once

#include <echo/expression_template/concept.h>
#include <echo/execution_context.h>

namespace echo {
namespace expression_template {

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME)                       \
  struct NAME##AssignmentFunctor {                                      \
    template <class Lhs, class Rhs>                                     \
    auto operator()(Lhs & lhs,                                          \
                    const Rhs& rhs) const -> decltype(lhs SYMBOL rhs) { \
      return lhs SYMBOL rhs;                                            \
    }                                                                   \
  };
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT

template <class Derived, class Tag, class Scalar>
class ExpressionTemplateAssignment {
 public:
  using expression_template_tag = Tag;

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME)                              \
  template <class Rhs,                                                         \
            CONCEPT_REQUIRES(                                                  \
                concept::expression_template_node<Rhs>() /*&&                    \
                concept::mappable<NAME##AssignmentFunctor, Derived, Rhs>()*/)>   \
  auto operator SYMBOL(const Rhs& rhs) & {                                     \
    CONCEPT_ASSERT(concept::expression_template_node<Rhs>());                  \
    auto& derived = static_cast<Derived&>(*this);                              \
    return make_assignment_expression(                                         \
        expression_template_tag(), NAME##AssignmentFunctor(),                  \
        make_expression(expression_template_tag(), derived),                   \
        make_expression(expression_template_tag(), rhs));                      \
  }                                                                            \
  template <                                                                   \
      class OtherScalar,                                                       \
      CONCEPT_REQUIRES(                                                        \
          execution_context::concept::scalar<OtherScalar>() &&                 \
          std::is_convertible<OtherScalar, Scalar>::value /*&&                   \
          concept::mappable<NAME##AssignmentFunctor, Derived, OtherScalar>()*/)> \
  auto operator SYMBOL(OtherScalar rhs) & {                                    \
    auto& derived = static_cast<Derived&>(*this);                              \
    return make_assignment_expression(                                         \
        expression_template_tag(), NAME##AssignmentFunctor(),                  \
        make_expression(expression_template_tag(), derived),                   \
        make_expression(expression_template_tag(), rhs));                      \
  }
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT
};

template <class Derived, class Tag, class Scalar>
class ExpressionTemplateConstAssignment {
 public:
  using expression_template_tag = Tag;

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME)                              \
  template <class Rhs,                                                         \
            CONCEPT_REQUIRES(                                                  \
                concept::expression_template_node<Rhs>() /*&&                    \
                concept::mappable<NAME##AssignmentFunctor, Derived, Rhs>()*/)>   \
  auto operator SYMBOL(const Rhs& rhs) const {                                 \
    const auto& derived = static_cast<const Derived&>(*this);                  \
    return make_assignment_expression(                                         \
        expression_template_tag(), NAME##AssignmentFunctor(),                  \
        make_expression(expression_template_tag(), derived),                   \
        make_expression(expression_template_tag(), rhs));                      \
  }                                                                            \
  template <                                                                   \
      class OtherScalar,                                                       \
      CONCEPT_REQUIRES(                                                        \
          execution_context::concept::scalar<OtherScalar>() &&                 \
          std::is_convertible<OtherScalar, Scalar>::value /*&&                   \
          concept::mappable<NAME##AssignmentFunctor, Derived, OtherScalar>()*/)> \
  auto operator SYMBOL(OtherScalar rhs) {                                      \
    const auto& derived = static_cast<Derived&>(*this);                        \
    return make_assignment_expression(                                         \
        expression_template_tag(), NAME##AssignmentFunctor(),                  \
        make_expression(expression_template_tag(), derived),                   \
        make_expression(expression_template_tag(), rhs));                      \
  }
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT
};
}
}  // end namespace echo::expression_template
