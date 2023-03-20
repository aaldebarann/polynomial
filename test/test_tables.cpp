#include <gtest.h>
#include "UnorderedTB.h"
#include "OrderedTB.h"
#include "List_TB.h"
#include "Tree.h"

TEST(UnorderedTB, can_create_table) {
    ASSERT_NO_THROW(UnorderedTB table{});
}
TEST(OrderedTB, can_create_table) {
    ASSERT_NO_THROW(OrderedTB table{});
}
TEST(List_TB, can_create_table) {
    ASSERT_NO_THROW(List_TB table{});
}
TEST(Tree, can_create_table) {
    ASSERT_NO_THROW(Tree table{});
}
//TEST(UnorderedTB, insert_and_get) {
//    // nodes
//    Node n1;
//    n1.name = "pol1";
//    Polynome pol1 = Polynome{"x+y+z"};
//    n1.data = pol1;
//    Node n2;
//    n2.name = "pol2";
//    Polynome pol2 = Polynome{"x+y+z"};
//    n2.data = pol2;
//    Node n3;
//    Polynome pol3 = Polynome{"x*y*z"};
//    n3.data = pol3;
//    // table
//    UnorderedTB table;
//    // insert
//    table.Insert(n1);
//    table.Insert(n2);
//    table.Insert(n3);
//    // get back
//    Polynome get1 = table.Take_elem("pol1");
//    Polynome get2 = table.Take_elem("pol2");
//    Polynome get3 = table.Take_elem("pol3");
//
//    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3);
//}