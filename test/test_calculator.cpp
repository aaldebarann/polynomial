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
 */
TEST(Calculator, insert_and_get) {
    Calculator calc{};
    Polynome f{"42"};
    calc.insert("f", f);
    Polynome g{"x + y + z"};
    calc.insert("g", g);
    Polynome h{"x * y^2 * z^3"};
    calc.insert("h", h);
    // get back
    Polynome f1{calc.get("f")};
    Polynome g1{calc.get("g")};
    Polynome h1{calc.get("h")};
    EXPECT_TRUE(f == f1 && g == g1 && h == h1);
}
TEST(Calculator, calculate_polynome_expression) {
    Calculator calc{};
    Polynome f{"3"};
    calc.insert("f", f);
    Polynome g{"x + y"};
    calc.insert("g", g);
    Polynome h{"x + z"};
    calc.insert("h", h);
    // get back
    ArithmeticExpression expression("2*(g + h) * f");
    Polynome expected{"12*x + 6*y + 6*z"};
    Polynome actual = expression.calculate(calc.activeTable());
    EXPECT_EQ(expected.to_string(), actual.to_string());
}
TEST(Calculator, can_interpret_inizialization) {
    Calculator calc{};

    calc.interpret("f = x*y*z");
    calc.interpret("g = x*y*z"); // g = x*y*z
    calc.interpret("h = x*y*z");

    Polynome expected{"x*y*z"};

    Polynome f {calc.get("f")};
    EXPECT_EQ(expected.to_string(), f.to_string());

    Polynome g {calc.get("g")};
    EXPECT_EQ(expected.to_string(), g.to_string());

    Polynome h {calc.get("h")};
    EXPECT_EQ(expected.to_string(), h.to_string());

}
TEST(Calculator, can_interpret_expression) {
    Calculator calc{};

    Polynome f{"y + z"};
    calc.insert("f", f);
    Polynome g{"x + y"};
    calc.insert("g", g);
    Polynome h{"x + z"};
    calc.insert("h", h);
    Polynome a{"12"};
    calc.insert("a", a);
    Polynome b{"13"};
    calc.insert("b", b);
    Polynome c{"14"};
    calc.insert("c", c);

    Polynome expected{"12*x + 6*y + 6*z"};
    string actual = calc.interpret("2*(g + h) * f");

    EXPECT_EQ(expected.to_string(), actual);

}
TEST(Calculator, can_interpret) {
    Calculator calc{};

    calc.interpret("f = 3");
    calc.interpret("g = x + y");
    calc.interpret("h = x + z");
    string actual = calc.interpret("2*(g + h) * f");

    Polynome expected{"12*x + 6*y + 6*z"};

    EXPECT_EQ(expected.to_string(), actual);
}
TEST(Calculator, can_interpret_huge_set) {
    Calculator calc{};

    calc.interpret("f = y + z");
    calc.interpret("g = x + y");
    calc.interpret("h = x + z");
    calc.interpret("a = 12");
    calc.interpret("b = 13");
    calc.interpret("c = 14");
    calc.interpret("xx = x^2");
    calc.interpret("yy = y^2");
    calc.interpret("zz = z^2");
    string actual = calc.interpret("(xx + yy*zz) * b");

    Polynome expected{"13*x^2 + 13*y^2*z^2"};

    EXPECT_EQ(expected.to_string(), actual);
}