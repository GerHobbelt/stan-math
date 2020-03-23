#ifndef STAN_MATH_PRIM_FUN_ATAN_HPP
#define STAN_MATH_PRIM_FUN_ATAN_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/fun/Eigen.hpp>
#include <cmath>

namespace stan {
namespace math {

/**
 * Structure to wrap \c atan() so it can be vectorized.
 *
 * @tparam T type of variable
 * @param x variable
 * @return Arctan of x in radians.
 */
struct atan_fun {
  template <typename T>
  static inline T fun(const T& x) {
    using std::atan;
    return atan(x);
  }
};

/**
 * Returns the elementwise \c atan() of the input,
 * which may be a scalar or any Stan container of numeric scalars.
 *
 * @tparam Container type of container
 * @param x container
 * @return Arctan of each value in x, in radians.
 */
template <
    typename Container,
    require_not_container_st<is_container, std::is_arithmetic, Container>...>
inline auto atan(const Container& x) {
  return apply_scalar_unary<atan_fun, Container>::apply(x);
}

/**
 * Version of atan() that accepts std::vectors, Eigen Matrix/Array objects,
 *  or expressions, and containers of these.
 *
 * @tparam Container Type of x
 * @param x Container
 * @return Elementwise atan of members of container.
 */
template <typename Container,
          require_container_st<is_container, std::is_arithmetic, Container>...>
inline auto atan(const Container& x) {
  return apply_vector_unary<Container>::apply(
      x, [](const auto& v) { return v.array().atan(); });
}

}  // namespace math
}  // namespace stan

#endif
