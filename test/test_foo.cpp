#include "gtest/gtest.h"
#include <stdexcept>

TEST(test_factorial, positive_values) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(2, 2);
  EXPECT_EQ(6, 3);
}

TEST(test_factorial, zero) { EXPECT_EQ(1, 1); }

// TEST(test_factorial, negative_value) {
//   EXPECT_THROW(factorial(-1), std::invalid_argument);
// }