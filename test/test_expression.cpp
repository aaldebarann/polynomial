#include <gtest.h>
#include "expression.h"
#include <iostream>
#include <UnorderedTB.h>

TEST(ArithmeticExpression, can_parse_vars_only_expression) {
    string str = " _var1_ *  var2 + VAR3-  vAr_4 -v  *  ___var_6*var_______7";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_digits_only_expression) {
    string str = "   2*4 -4.0 + 0.4 * .4 * 3. - 4      - 7";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_vars_digits_expression) {
    string str = "   2*4 -4.0*_var1_ + 0.4 * .4 * 3. - f   +vAr_2   - 7";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_brackets_expression) {
    string str = " (  ((2)*4) -(4.0*_var1_ + 0.4) * (.4 * 3.) - f   +vAr_2   - 7)";
    ASSERT_NO_THROW(ArithmeticExpression expression(str));
}
TEST(ArithmeticExpression, can_parse_function_expression) {
    string str = "4 - min(1,3,-2) + (FUNC_1 ( a, b) * FUNC_2 (1, 2, 3, 4., pyat) ) - sqrt(42)";
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
    string str = "3 + min(x, sqrt(y))";
    ASSERT_ANY_THROW(ArithmeticExpression expression(str));
}

TEST(ArithmeticExpression, can_get_infix)
{
    ArithmeticExpression expression("aaa - 123.23 +b*c*.124-d");

    EXPECT_EQ("aaa-123.23+b*c*.124-d", expression.getString());
}
TEST(ArithmeticExpression, correct_infix_no_functions) {
    string str = "(  ((2)*4) -(4.0*_var1_ + 0.4) * (.4 * 3.) - o_0   +vAr_2   - 7)";
    vector<pair<ArithmeticExpression::LType, string>> expected = {
            {ArithmeticExpression::begin,  "("},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::number,  "2"},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "*"},
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
            {ArithmeticExpression::operation, "*"},
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
    EXPECT_EQ(expected, expr.getInfix());
}

TEST(ArithmeticExpression, correct_infix_functions) {
    string str = "(  (8 - sqrt(3)*pi) * MIN(a, b))";
    vector<pair<ArithmeticExpression::LType, string>> expected = {
            {ArithmeticExpression::begin,  "("},
            {ArithmeticExpression::begin, "("},
            {ArithmeticExpression::number,  "8"},
            {ArithmeticExpression::operation, "-"},
            {ArithmeticExpression::function, "sqrt"},
            {ArithmeticExpression::fbegin, "("},
            {ArithmeticExpression::numArg, "3"},
            {ArithmeticExpression::fend, ")"},
            {ArithmeticExpression::operation, "*"},
            {ArithmeticExpression::variable,  "pi"},
            {ArithmeticExpression::end, ")"},
            {ArithmeticExpression::operation, "*"},
            {ArithmeticExpression::function, "MIN"},
            {ArithmeticExpression::fbegin, "("},
            {ArithmeticExpression::strArg, "a"},
            {ArithmeticExpression::comma, ","},
            {ArithmeticExpression::strArg, "b"},
            {ArithmeticExpression::fend, ")"},
            {ArithmeticExpression::end, ")"},
    };
    ArithmeticExpression expr = ArithmeticExpression(str);
    EXPECT_EQ(expected, expr.getInfix());
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
    EXPECT_EQ("2min(1,3)+max(a,b)-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_function_different_priority)
{
    ArithmeticExpression expression("2 + min(1, 3)*f(2) - max(a, b)*f(5)");
    EXPECT_EQ("2min(1,3)f(2)*+max(a,b)f(5)*-", expression.getPostfix());
}
TEST(ArithmeticExpression, can_get_postfix_function_brackets)
{
    ArithmeticExpression expression("a_0(f) * 2 + pi*( I(p1, dx, a, b) - D(p2, p4, 12) * 8) * 1");
    EXPECT_EQ("a_0(f)2*piI(p1,dx,a,b)D(p2,p4,12)8*-*1*+", expression.getPostfix());
}

TEST(ArithmeticExpression, can_calculate_subtraction_digits_only)
{
    ArithmeticExpression expression(" 3 - 2 - (3 - 4)");

    Polynome result = expression.calculate();
    float exp = 3 - 2 - (3 - 4);
    Polynome expected{ exp };

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_multiplication_digits_only)
{
    ArithmeticExpression expression(" 1 * 2 * (3 * 4)");

    Polynome result = expression.calculate();
    float exp = 1 * 2 * (3 * 4);
    Polynome expected{ exp };

    EXPECT_TRUE(expected == result);
}
TEST(ArithmeticExpression, can_calculate_division_digits_only)
{
    ArithmeticExpression expression(" 1.0 * 2.0 * (3.0 * 4.0)");

    Polynome result = expression.calculate();
    float exp = 1.0 * 2.0 * (3.0 * 4.0);
    Polynome expected{ exp };

    EXPECT_TRUE(expected == result);
}
TEST(ArithmeticExpression, can_calculate_digits_only)
{
    ArithmeticExpression expression("(1.0 * 2.0 - (3.0 * 4.0) * 5.0 + 0.6 - 0.7*0.7) * (0.1 + 0.2)");

    Polynome result = expression.calculate();
    float exp = (1.0 * 2.0 - (3.0 * 4.0) * 5.0 + 0.6 - 0.7*0.7) * (0.1 + 0.2);
    Polynome expected{ exp };

    EXPECT_TRUE(expected == result);
}
TEST(ArithmeticExpression, can_calculate_sqrt)
{
    ArithmeticExpression expression("(5 - (sqrt(4))*(sqrt(4))) - sqrt(3)*sqrt(3)");

    Polynome result = expression.calculate();
    float exp = 5 - sqrt(4)*sqrt(4) - sqrt(3)*sqrt(3);
    Polynome expected{ exp };

    EXPECT_TRUE(expected == result);
}
Table* sampleTable () {
    auto* table = new UnorderedTB();
    Node node;

    Polynome a{"x"};
    Polynome b{"y"};
    Polynome c{"z"};
    Polynome d{"-1*x"};
    Polynome e{"x + y + z"};

    node.data = a;
    node.name = "a";
    table->Insert(node);
    node.data = b;
    node.name = "b";
    table->Insert(node);
    node.data = c;
    node.name = "c";
    table->Insert(node);
    node.data = d;
    node.name = "d";
    table->Insert(node);
    node.data = e;
    node.name = "e";
    table->Insert(node);

    return table;
}
TEST(ArithmeticExpression, can_calculate_polynomial_additiony)
{
    ArithmeticExpression expression(" a + b + (c + d) + (b + b)");

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{"3*y + z"};

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_polynomial_multiplication)
{
    ArithmeticExpression expression(" a * b * (c * d)");

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{ "-1*x^2*y*z" };

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_polynomial_differetial_sum)
{
    ArithmeticExpression expression("D(a, x) + D(b, y) + D(c, z) + D(d, x)");

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{ "2" };

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_polynomial_integral_sum)
{
    ArithmeticExpression expression("I(a, x) + I(b, y) + I(c, z) + I(d, x)");

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{ "0.5*y^2 + 0.5*z^2" };

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_polynomial_value_at)
{
    ArithmeticExpression expression("AT(d, 1, 2, 3) + AT(e, 1, 2, 3)");

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{ "5" };

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
TEST(ArithmeticExpression, can_calculate_polynomial)
{
    ArithmeticExpression expression("AT(a, 1, 2, 3) + D(b, y) + I(c, z)  - d*e");
    // 1 + 1 + 0.5*z^2 - (-x) * (x+y+z)

    Table* pTable = sampleTable();

    Polynome result = expression.calculate(pTable);
    Polynome expected{ "2 + 0.5*z^2  + x^2 + x*y + x*z" };

    delete pTable;

    EXPECT_EQ(expected.to_string(), result.to_string());
}
