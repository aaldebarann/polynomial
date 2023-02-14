#include <gtest.h>
#include "expression.h"

TEST(ArithmeticExpression, can_parse_vars_only_expression) {
  string str = " _var1_ *  var2 + VAR3-  vAr_4 -v  /  ___var_6/var_______7";
  ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_digits_only_expression) {
    string str = "   2/4 -4.0 + 0.4 * .4 / 3. - 4      - 7";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_vars_digits_expression) {
    string str = "   2/4 -4.0*_var1_ + 0.4 * .4 / 3. - f   +vAr_2   - 7";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_brackets_expression) {
    string str = " (  ((2)/4) -(4.0*_var1_ + 0.4) * (.4 / 3.) - f   +vAr_2   - 7)";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}

TEST(ArithmeticExpression, throws_when_empty_string) {
    string str = "";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_empty_brackets) {
    string str = " a + 3*b + () - 4";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_unclosed_bracket) {
    string str = "( (a + (3*b) - 4) + 2";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_unopened_bracket) {
    string str = "(a + (3*b) - 4) + 2 )";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_operation_lost) {
    string str = "a + 3b + 4";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_double_operation) {
    string str = "a + 3b ++ 4";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_invalid_symbols) {
    string str = "a + 3b^ + 4";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}

TEST(ArithmeticExpression, can_get_infix)
{
    ArithmeticExpression expression("aaa - 123.23 +b*c/.124-d");

    EXPECT_EQ("aaa-123.23+b*c/.124-d", expression.getInfix());
}

TEST(ArithmeticExpression, can_get_postfix_equal_priority)
{
  ArithmeticExpression expression("a   + b - c      - d");
  EXPECT_EQ("ab+c-d-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_different_priority)
{
  ArithmeticExpression expression("  a+b*c -  e  - d*e");
  EXPECT_EQ("abc*+e-de*-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_brackets)
{
  ArithmeticExpression expression("  a+b*(c -  e)  - d*e + (f+g*(j-i))");
  EXPECT_EQ("abce-*+de*-fgji-*++", expression.getPostfix());
}

TEST(ArithmeticExpression, can_calculate_addition_vars_only)
{
    ArithmeticExpression expression(" a + b + (c + d)");
    istringstream values("1 2 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 + 2 + (3 + 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_addition_repeated_variables_vars_only)
{
    ArithmeticExpression expression(" a + b + (b + a) + a + a");
    istringstream values("1 2");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 + 2 + (2 + 1) + 1 + 1;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_subtraction_vars_only)
{
    ArithmeticExpression expression(" a - b - (c - d)");
    istringstream values("1 2 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 - 2 - (3 - 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_subtraction_repeated_variables_vars_only)
{
    ArithmeticExpression expression(" a - b - (b - a) - a - a");
    istringstream values("1 2");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 - 2 - (2 - 1) - 1 - 1;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_multiplication_vars_only)
{
    ArithmeticExpression expression(" a * b * (c * d)");
    istringstream values("1 2 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 * 2 * (3 * 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_multiplication_repeated_variables_vars_only)
{
    ArithmeticExpression expression(" a * b * (b * a) * a * a");
    istringstream values("2 3");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 2 * 3 * (3 * 2) * 2 * 2;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_division_vars_only)
{
    ArithmeticExpression expression(" a / b / (c / d)");
    istringstream values("1 2 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1.0 / 2.0 / (3.0 / 4.0);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_division_repeated_variables_vars_only)
{
    ArithmeticExpression expression(" a / b / (b / a) / a / a");
    istringstream values("2 3");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 2.0 / 3.0 / (3.0 / 2.0) / 2.0 / 2.0;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_vars_only)
{
    ArithmeticExpression expression("( a / b - (c / d) * e + f ) ");
    istringstream values("2 4 3 6 5 6");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = (2.0 / 4.0 - (3.0 / 6.0) * 5.0 + 6.0 ) ;

    EXPECT_EQ(expected, result);
}

TEST(ArithmeticExpression, can_calculate_subtraction_digits_only)
{
    ArithmeticExpression expression(" 1 - 2 - (3 - 4)");
    ostream nowhere(nullptr);

    double result = expression.calculate(cin, nowhere);
    double expected = 1 - 2 - (3 - 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_multiplication_digits_only)
{
    ArithmeticExpression expression(" 1 * 2 * (3 * 4)");

    ostream nowhere(nullptr);

    double result = expression.calculate(cin, nowhere);
    double expected = 1 * 2 * (3 * 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_division_digits_only)
{
    ArithmeticExpression expression(" 1.0 / 2.0 / (3.0 / 4.0)");
    ostream nowhere(nullptr);

    double result = expression.calculate(cin, nowhere);
    double expected = 1.0 / 2.0 / (3.0 / 4.0);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_digits_only)
{
    ArithmeticExpression expression("(1.0 / 2.0 - (3.0 / 4.0) * 5.0 + 0.6 - 0.7*0.7) / (0.1 + 0.2)");
    ostream nowhere(nullptr);

    double result = expression.calculate(cin, nowhere);
    double expected = (1.0 / 2.0 - (3.0 / 4.0) * 5.0 + 0.6 - 0.7*0.7) / (0.1 + 0.2);

    EXPECT_EQ(expected, result);
}

TEST(ArithmeticExpression, can_calculate_addition)
{
    ArithmeticExpression expression(" a + 2.0 + (c + d)");
    istringstream values("1 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 + 2 + (3 + 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_subtraction)
{
    ArithmeticExpression expression(" a - 2 - (c - d)");
    istringstream values("1 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 - 2 - (3 - 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_multiplication)
{
    ArithmeticExpression expression(" a * 2222 * (c * d)");
    istringstream values("1 3 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1 * 2222 * (3 * 4);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate_division)
{
    ArithmeticExpression expression(" a / b / (0.3 / d)");
    istringstream values("1 2 4");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = 1.0 / 2.0 / (0.3 / 4.0);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_calculate)
{
    ArithmeticExpression expression("( a / b - (c / d) * e + f - 0.7*g) / (1.0 + 2.0)");
    istringstream values("1 2 3 4 5 0.6 .7");
    ostream nowhere(nullptr);

    double result = expression.calculate(values, nowhere);
    double expected = (1.0 / 2.0 - (3.0 / 4.0) * 5.0 + 0.6 - 0.7*0.7) / (1.0 + 2.0);

    EXPECT_EQ(expected, result);
}
