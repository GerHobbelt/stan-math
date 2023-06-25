#include <stan/math/mix.hpp>
#include <test/unit/math/test_ad.hpp>

TEST(mathMixScalFun, neg_binomial_2_log_glm_lpmf) {
  auto f = [](const int y, const auto& x) {
    return [=](const auto& alpha, const auto& beta, const auto& phi) {
      return stan::math::neg_binomial_2_log_glm_lpmf(y, x, alpha, beta, phi);
    };
  };
  auto f2 = [](const int y, const auto& phi) {
    return [=](const auto& x, const auto& alpha, const auto& beta) {
      return stan::math::neg_binomial_2_log_glm_lpmf(y, x, alpha, beta, phi);
    };
  };

  Eigen::MatrixXd x = Eigen::MatrixXd::Random(2, 2);
  Eigen::VectorXd alpha = Eigen::VectorXd::Random(2);
  Eigen::VectorXd beta = Eigen::VectorXd::Random(2);
  double phi = 1.5;

  stan::test::expect_ad(f(0, x), alpha, beta, phi);
  stan::test::expect_ad(f2(0, phi), x, alpha, beta);
  stan::test::expect_ad(f(1, x), alpha, beta, phi);
  stan::test::expect_ad(f2(1, phi), x, alpha, beta);
}
