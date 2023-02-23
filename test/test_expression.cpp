#include <gtest.h>
#include "expression.h"
#include <iostream>

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
TEST(ArithmeticExpression, can_parse_function_expression) {
    string str = "4 - min(1,3,-2) + (FUNC_1 ( a, b) / FUNC_2 (1, 2, 3, 4., pyat) ) - f(42)";
    ArithmeticExpression expression(str);
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

TEST(ArithmeticExpression, throws_when_no_arguments_function)
{
    string str = "3 + min()";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_extra_comma_in_function)
{
    string str = "3 + min(x, y, 12,)";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, throws_when_function_in_function)
{
    string str = "3 + min(x, y, 12,)";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}

TEST(ArithmeticExpression, can_get_infix)
{
    ArithmeticExpression expression("aaa - 123.23 +b*c/.124-d");

    EXPECT_EQ("aaa-123.23+b*c/.124-d", expression.getString());
}
TEST(ArithmeticExpression, correct_infix_no_functions) {
    string str = "(  ((2)/4) -(4.0*_var1_ + 0.4) * (.4 / 3.) - o_0   +vAr_2   - 7)";
    vector<pair<ArithmeticExpression::LType, string>> expected = {
            {ArithmeticExpression::begin,  "("},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::number,  "2"},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "/"},
            {ArithmeticExpression::number,  "4"},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "-"},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::number,  "4.0"},
            {ArithmeticExpression::operation, "*"},
            {ArithmeticExpression::variable,  "_var1_"},
            {ArithmeticExpression::operation, "+"},
            {ArithmeticExpression::number,  "0.4"},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "*"},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::number,  ".4"},
            {ArithmeticExpression::operation, "/"},
            {ArithmeticExpression::number,  "3."},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "-"},
            {ArithmeticExpression::variable,  "o_0"},
            {ArithmeticExpression::operation, "+"},
            {ArithmeticExpression::variable,  "vAr_2"},
            {ArithmeticExpression::operation, "-"},
            {ArithmeticExpression::number,  "7"},
            {ArithmeticExpression::end, ")"},
    };
    ArithmeticExpression expr = ArithmeticExpression(str);
    EXPECT_EQ(expr.getInfix(), expected);
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
TEST(ArithmeticExpression, can_get_postfix_function_equal_priority)
{
    ArithmeticExpression expression("2 + min(1, 3) - max(a, b)");
    cout << expression.getPostfix() << endl;
    EXPECT_EQ("2min(1,3)+max(a,b)-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_function_different_priority)
{
    ArithmeticExpression expression("2 + min(1, 3)*f(2) - max(a, b)/f(5)");
    cout << expression.getPostfix() << endl;
    EXPECT_EQ("2min(1,3)f(2)*+max(a,b)f(5)/-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_function_brackets)
{
    ArithmeticExpression expression("a_0(f) / 2 + pi*( I(p1, dx, a, b) - D(p2, p4, 12) * 8) / 1");
    EXPECT_EQ("a_0(f)2/piI(p1,dx,a,b)D(p2,p4,12)8*-*1/+", expression.getPostfix());
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
