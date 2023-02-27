#include <gtest.h>
#include "polynomial.h"
int main(int argc, char **argv)
{
    Polynome p("3*x^2*y^3");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
