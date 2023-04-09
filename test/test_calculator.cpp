//
// Created by Алексей on 18.03.2023.
//
#include <gtest.h>
#include "calculator.h"

TEST(Calculator, can_construct){
    ASSERT_NO_THROW(Calculator calc{false});
}
TEST(Calculator, can_destruct){
    auto* calc = new Calculator{false};
    ASSERT_NO_THROW(delete calc);
}
TEST(Calculator, can_set_active_table) {
    auto* calc = new Calculator{true};
    ASSERT_NO_THROW(calc->setActive(0));
    ASSERT_NO_THROW(calc->setActive(1));
    ASSERT_NO_THROW(calc->setActive(2));
    ASSERT_NO_THROW(calc->setActive(3));
    ASSERT_NO_THROW(calc->setActive(4));
    ASSERT_NO_THROW(calc->setActive(2));
}
TEST(Calculator, can_insert) {
    auto* calc = new Calculator{false};
    Polynome a{"x"};
    Polynome b{"y"};
    Polynome c{"z"};
    Polynome d{"x^2"};
    Polynome e{"y^2"};
    Polynome f{"z^2"};
    Polynome g{"x*y"};
    Polynome h{"x*z"};
    Polynome i{"y*z"};
    ASSERT_NO_THROW(calc->insert("a", a));
    ASSERT_NO_THROW(calc->insert("b", b));
    ASSERT_NO_THROW(calc->insert("c", c));
    ASSERT_NO_THROW(calc->insert("d", d));
    ASSERT_NO_THROW(calc->insert("e", e));
    ASSERT_NO_THROW(calc->insert("f", f));
    ASSERT_NO_THROW(calc->insert("g", g));
    ASSERT_NO_THROW(calc->insert("h", h));
    ASSERT_NO_THROW(calc->insert("i", i));
    ASSERT_NO_THROW(delete calc);
}
TEST(Calculator, insert_and_get) {
    Calculator calc{false};
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
TEST(Calculator, insert_and_get_all) {
  Calculator calc{ true };
  Polynome f{ "42" };
  calc.insert("f", f);
  Polynome g{ "x + y + z" };
  calc.insert("g", g);
  Polynome h{ "x * y^2 * z^3" };
  calc.insert("h", h);
  // get back
  Polynome f1{ calc.get("f") };
  Polynome g1{ calc.get("g") };
  Polynome h1{ calc.get("h") };
  EXPECT_TRUE(f == f1 && g == g1 && h == h1);
}
TEST(Calculator, calculate_polynome_expression) {
    Calculator calc{false};
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
    Calculator calc{true};

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
    Calculator calc{true};

    Polynome f{"y + z"};
    calc.insert("f", f);
    Polynome g{"x + y"};
    calc.insert("g", g);
    Polynome h{"x + z"};
    calc.insert("h", h);

    string actual = calc.interpret("2*(g + h) * f");
    // 2*(2x + y + z) * (y + z)
    Polynome expected{"4*x*y + 4*x*z + 2*y^2 + 4*y*z + 2*z^2"};

    EXPECT_EQ(expected.to_string(), actual);

}
TEST(Calculator, can_interpret) {
    Calculator calc{true};

    calc.interpret("f = y + z");
    calc.interpret("g = x + y");
    calc.interpret("h = x + z");

    string actual = calc.interpret("2*(g + h) * f");
    // 2*(2x + y + z) * (y + z)
    Polynome expected{"4*x*y + 4*x*z + 2*y^2 + 4*y*z + 2*z^2"};

    EXPECT_EQ(expected.to_string(), actual);
}
TEST(Calculator, can_interpret_huge_set) {
    Calculator calc{true};

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
TEST(Calculator, re_assignment) {
  Calculator calc{ true };
  
  calc.interpret("f = x");
  calc.interpret("f = y");
  calc.interpret("f = z");
  calc.interpret("f = x");
  calc.interpret("f = y");
  calc.interpret("f = z");
  
  Polynome actual = calc.get("f");
  Polynome expected = Polynome("z");

  EXPECT_EQ(expected.to_string(), actual.to_string());
}
TEST(Calculator, complex_assignment) {
  Calculator calc{ true };
  //Polynome p("5 * x^2+3*x");
  //p.print();
  //cout << p.to_string() << endl;
  calc.interpret("f = x");
  calc.interpret("g = y");
  calc.interpret("h = z");
  calc.interpret("p = f + g*h");

  Polynome actual = calc.get("p");
  Polynome expected = Polynome("x + y*z");

  EXPECT_EQ(expected.to_string(), actual.to_string());
}

TEST(Calculator, can_interpret_huge_set_all_tables) {
    Calculator calc{true};

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