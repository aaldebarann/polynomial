#include <gtest.h>
#include "polynomial.h"

TEST(Polynome,can_create_polynomes){
    ASSERT_NO_THROW(Polynome("3 * x^2 + 5 * x * z - y"));
}


TEST(Polynome,can_add_polynomes){
    Polynome p1("2* x + y");
    Polynome p2("-x + z + y");
    auto p3 = p1 + p2;
    //cout << "Here it is: " << endl;
    //p3.print();
    ASSERT_NO_THROW(auto p3 = p1 + p2;);
}

TEST(Polynome,can_add_polynomes_properly){
    Polynome p1("2* x + y");
    Polynome p2("z - x + y");
    auto p3 = p1 + p2;
    auto p4 = Polynome("x+z+2*y");
    bool r = (p3 == p4);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_subtract_polynomes){
    Polynome p1("2* x + y");
    Polynome p2("-x + z + y");
    ASSERT_NO_THROW(auto p3 = p1 - p2;);
}

TEST(Polynome,can_subtract_polynomes_properly){
    Polynome p1("2* x + y");
    Polynome p2("-x + z + y");
    auto p3 = p1 - p2;
    auto p4 = Polynome("3*x-z");
    bool r = (p3 == p4);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_multiply_polynome_by_a_constant){
    Polynome p1("2* x + y");
    Polynome p2 = p1 * 2.5;
    auto p3 = Polynome("5*x+2.5*y");
    bool r = (p3 == p2);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_differentiate_polynome_properly){
    Polynome p1("2* x * z + y");
    Polynome p2 = p1.differentiate(0);
    //p2.print();
    auto p3 = Polynome("2 * z");
    bool r = (p3 == p2);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_integrate_polynome_properly){
    Polynome p1("2* x * z + y*z+z");
    Polynome p2 = p1.integrate(2);
    //p2.print();
    auto p3 = Polynome("x * z^2 + 0.5 * y * z^2+0.5 * z^2");
    bool r = (p3 == p2);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_multiply_polynomes_properly){
    Polynome p1("x^2+2*y");
    Polynome p2("y-z");
    //p2.print();
//    Polynome p10("1.2356 * x^2-15.7689 * y");
//    cout << "IT'S HERE!!!!"<< endl;
//    p10.print();
//    cout << "IT'S HERE!!!!"<< endl;
    auto p3 = p1 * p2;
    Polynome p4("x^2*y-x^2*z+2*y^2-2*y*z");
    bool r = (p3 == p4);
    ASSERT_EQ(r,1);
}

TEST(Polynome,can_translate_polynomes_properly){
    Polynome p1("x^2+2*y-8*y*z");
    list<Monome> add_list;
    add_list.emplace_back(1,2,0,0);
    add_list.emplace_back(2,0,1,0);
    add_list.emplace_back(-8,0,1,1);
    Polynome p2(add_list);
    bool r = (p1 == p2);
    ASSERT_EQ(r,1);
}
TEST(Polynome,can_find_value_at_point_properly){
    Polynome p1("x^2+2*y-8*y*z");
    auto v = p1.value_at(0,1,1);
    ASSERT_EQ(v,-6);
}
TEST(Polynome, to_string) {
    Polynome f("x");
    Polynome g("y");
    Polynome h("z");
    Polynome result = f +  g * h;
    Polynome expected("x + y*z");

    EXPECT_EQ(expected.to_string(), result.to_string());
}