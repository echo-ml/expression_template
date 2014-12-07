#pragma once

#include <echo/concept.h>

namespace echo { namespace expression_template {

TICK_TRAIT(is_expression_template_node) {
  template<class T>
  auto requires_(const T& node) -> tick::valid<
      has_type<typename T::expression_template_tag>
    , decltype(make_expression(typename T::expression_template_tag(), node))
  >;
};

}} //end namespace
