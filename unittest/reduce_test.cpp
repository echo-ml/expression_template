#include <echo/expression_template/reduce.h>
#include <echo/execution_context/expression.h>
#include <echo/test.h>
using namespace echo;
using namespace echo::expression_template;

struct my_expression_tag {};

struct E {
  using expression_template_tag = my_expression_tag;
  using structure = execution_context::structure::general;
  auto dimensionality() const {
    return DimensionalityC<2, 3>();
  }
  double operator()(index_t i, index_t, index_t j, index_t) const {
    return i+j;
  }
  const auto& evaluator() const {
    return *this;
  }
};

auto make_expression(my_expression_tag, const E& e) { return e; }

template<class Identity, class Mapper, class Reducer>
struct R {
  Identity _identity;
  Mapper _mapper;
  Reducer _reducer;
  using structure = execution_context::structure::general;
  auto dimensionality() const {
    return DimensionalityC<2,3>();
  }
  const auto& identity() const { return _identity; }
  const auto& mapper() const { return _mapper; }
  const auto& reducer() const { return _reducer; }
};

template<class Identity, class Reducer, class Expression>
auto make_reduction_expression(my_expression_tag,
  Identity identity, Reducer reducer, const Expression& expression)
{
  auto evaluator = expression.evaluator();
  return R<Identity, decltype(evaluator), Reducer>{
    identity, evaluator, reducer
  };
}

TEST_CASE("reduce") {
  E e;
  auto reduction = sum_elements(e);
}
