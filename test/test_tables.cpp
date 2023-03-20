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
TEST(UnorderedTB, insert_and_get_unord) {
    // nodes
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.name = "pol3";
    n3.data = pol3;
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3);
}
TEST(UnorderedTB, delete_elem_unord) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.name = "pol3";
    n3.data = pol3;
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(UnorderedTB, print_elem_unord) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Print());
}
TEST(OrderedTB, delete_elem_ord) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(OrderedTB, insert_and_get_ord) {
    // nodes
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    OrderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3);
}
TEST(OrderedTB, print_elem_ord) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Print());
}
TEST(List_TB, insert_and_get_List_TB) {
    // nodes
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    List_TB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3);
}
TEST(List_TB, delete_elem_List_TB) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    List_TB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(List_TB, print_elem_List_TB) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    List_TB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Print());
}
TEST(Tree, insert_and_get_Tree) {
    // nodes
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
    n3.name = "pol3";
    // table
    Tree table;
    // insert
    Obj* o = NULL;
    table.Insert(n1,o);
    table.Insert(n2,o);
    table.Insert(n3,o);
    // get back
    Polynome get1 = table.find("pol1",o);
    Polynome get2 = table.find("pol2",o);
    Polynome get3 = table.find("pol3",o);

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3);
}

TEST(Tree, delete_elem_Tree) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
     n3.name = "pol3";
    // table
    Obj* o = NULL;
    Tree table;
    // insert
    table.Insert(n1, o);
    table.Insert(n2, o);
    table.Insert(n3, o);

    ASSERT_NO_THROW(table.Del(n2.name,o));
}
TEST(Tree, print_elem_Tree) {
    Node n1;
    n1.name = "pol1";
    Polynome pol1 = Polynome{ "x+y+z" };
    n1.data = pol1;
    Node n2;
    n2.name = "pol2";
    Polynome pol2 = Polynome{ "x+y+z" };
    n2.data = pol2;
    Node n3;
    Polynome pol3 = Polynome{ "x*y*z" };
    n3.data = pol3;
     n3.name = "pol3";
    // table
    Obj* o = NULL;
    Tree table;
    // insert
    table.Insert(n1, o);
    table.Insert(n2, o);
    table.Insert(n3, o);

    ASSERT_NO_THROW(table.preorder(o));
}

