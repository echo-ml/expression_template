#pragma once

#include <echo/expression_template/expression.h>
#include <echo/enable_if.h>

namespace echo { namespace expression_template {

template<class Tag, class Functor, class Lhs, class Rhs>
auto make_assignment_expression(Tag, Functor, const Lhs&, const Rhs&);

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME) \
  struct NAME ## AssignmentFunctor { \
      template<class Lhs, class Rhs> \
      auto& operator()(Lhs& lhs, const Rhs& rhs) const { \
        return lhs SYMBOL rhs; \
      } \
  };
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT

template<class Derived, class Tag, class Scalar>
class ExpressionTemplateAssignment {
 public:
  using expression_template_tag = Tag;

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME) \
    template< \
        class Rhs \
      , enable_if<is_expression_template_node<Rhs>> = 0 \
    > \
    auto operator SYMBOL (const Rhs& rhs) { \
      auto& derived = static_cast<Derived&>(*this); \
      return make_assignment_expression(expression_template_tag() \
                                      , NAME ## AssignmentFunctor() \
                                      , make_expression(expression_template_tag(), derived) \
                                      , make_expression(expression_template_tag(), rhs)); \
    } \
    auto operator SYMBOL (Scalar rhs) { \
      auto& derived = static_cast<Derived&>(*this); \
      return make_assignment_expression(expression_template_tag() \
                                      , NAME ## AssignmentFunctor() \
                                      , make_expression(expression_template_tag(), derived) \
                                      , make_expression(expression_template_tag(), rhs)); \
    } 
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT
};

template<class Derived, class Tag, class Scalar>
class ExpressionTemplateConstAssignment {
 public:
  using expression_template_tag = Tag;

#define ECHO_ASSIGNMENT(SYMBOL, NAME, LOWER_NAME) \
    template< \
        class Rhs \
      , enable_if<is_expression_template_node<Rhs>> = 0 \
    > \
    auto operator SYMBOL (const Rhs& rhs) const { \
      const auto& derived = static_cast<const Derived&>(*this); \
      return make_assignment_expression(expression_template_tag() \
                                      , NAME ## AssignmentFunctor() \
                                      , make_expression(expression_template_tag(), derived) \
                                      , make_expression(expression_template_tag(), rhs)); \
    } \
    auto operator SYMBOL (Scalar rhs) const { \
      const auto& derived = static_cast<Derived&>(*this); \
      return make_assignment_expression(expression_template_tag() \
                                      , NAME ## AssignmentFunctor() \
                                      , make_expression(expression_template_tag(), derived) \
                                      , make_expression(expression_template_tag(), rhs)); \
    } 
#include <echo/expression_template/assignment-def.h>
#undef ECHO_ASSIGNMENT
};

}} //end namespace echo::expression_template
