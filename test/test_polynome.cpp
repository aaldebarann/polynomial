#include <gtest.h>
#include "polynomial.h"

TEST(Polynome,can_create_polynomes){
    ASSERT_NO_THROW(Polynome("3 * x^2 + 5 * x * z - y"));
}
