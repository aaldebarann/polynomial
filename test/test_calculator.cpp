//
// Created by Алексей on 18.03.2023.
//
#include <gtest.h>
#include "calculator.h"

TEST(Calculator, can_construct){
    ASSERT_NO_THROW(Calculator calc{});
}
TEST(Calculator, can_destruct){
    auto* calc = new Calculator{};
    ASSERT_NO_THROW(delete calc);
}
TEST(Calculator, can_insert) {
    Calculator calc{};
    Polynome p("x+3*x*y*z");
    ASSERT_NO_THROW(calc.insert("p1", p));
}
/* strange error
 * error: no match for 'operator==' (operand types are 'const Polynome' and 'const Polynome')
TEST(Calculator, insert_and_get) {
    Calculator calc{};
    Polynome p{"x+3*x*y*z"};
    calc.insert("p1", p);
    Polynome fromTable{calc.get("p1")};
    EXPECT_EQ(p, fromTable);
}
 *//*
TEST(Calculator, insert_and_get) {
    Calculator calc{};
    Polynome f{"42"};
    calc.insert("f", f);
    Polynome g{"x^42"};
    calc.insert("g", g);
    Polynome h{"42*x^42*y^42*z^42"};
    calc.insert("h", h);
    // get back
    Polynome f1{calc.get("f")};
    Polynome g1{calc.get("g")};
    Polynome h1{calc.get("h")};
    EXPECT_TRUE(f == f1 && g == g1 && h == h1);
}*/