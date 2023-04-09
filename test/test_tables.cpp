#include <gtest.h>
#include "UnorderedTB.h"
#include "OrderedTB.h"
#include "List_TB.h"
#include "Tree.h"
#include "HashListTable.h"
#include "HashNextTable.h"
TEST(UnorderedTB, can_create_table) {
    ASSERT_NO_THROW(UnorderedTB table{});
}
TEST(OrderedTB, can_create_table) {
    ASSERT_NO_THROW(OrderedTB table{});
}
TEST(List_TB, can_create_table) {
    ASSERT_NO_THROW(List_TB table{});
}
TEST(HashListTable, can_create_table) {
    ASSERT_NO_THROW(HashListTable table{});
}
TEST(HashNextTable, can_create_table) {
    ASSERT_NO_THROW(HashNextTable table{});
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    UnorderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3 &&
    pol4 == get4 && pol5 == get5 && pol6 == get6);
}
TEST(HashListTable, insert_and_get_unord) {
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    HashListTable table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);

    //cout << table.to_string() <<endl;
    /*cout << "Printing table " << endl;
    table.Print();
    cout << "Printing table " << endl;*/
    // get back
    Polynome get1 = table.Take_elem("pol1");

    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3 &&
                pol4 == get4 && pol5 == get5 && pol6 == get6);
}
TEST(HashNextTable, insert_and_get_unord) {
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    HashNextTable table;
    // insert
    //cout << "Inserted new el: " << endl;
    table.Insert(n1);
    //table.Print();
    //cout << "Inserted new el: " << endl;
    table.Insert(n2);
    //table.Print();
    //cout << "Inserted new el: " << endl;
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);

    //cout << table.to_string() <<endl;
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_TRUE(pol1 == get1 && pol2 == get2 && pol3 == get3 &&
                pol4 == get4 && pol5 == get5 && pol6 == get6);
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
TEST(HashListTable, delete_elem_unord) {
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
    HashListTable table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(HashNextTable, delete_elem_unord) {
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
    HashNextTable table;
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
    OrderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(HashListTable, delete_elem_ord) {
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
    HashListTable table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
}
TEST(HashNextTable, delete_elem_ord) {
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
    HashNextTable table;
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    OrderedTB table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_EQ(pol1.to_string(), get1.to_string());
    EXPECT_EQ(pol2.to_string(), get2.to_string());
    EXPECT_EQ(pol3.to_string(), get3.to_string());
    EXPECT_EQ(pol4.to_string(), get4.to_string());
    EXPECT_EQ(pol5.to_string(), get5.to_string());
    EXPECT_EQ(pol6.to_string(), get6.to_string());

}
TEST(HashListTable, insert_and_get_ord) {
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    HashListTable table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);

    //cout << table.to_string()
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_EQ(pol1.to_string(), get1.to_string());
    EXPECT_EQ(pol2.to_string(), get2.to_string());
    EXPECT_EQ(pol3.to_string(), get3.to_string());
    EXPECT_EQ(pol4.to_string(), get4.to_string());
    EXPECT_EQ(pol5.to_string(), get5.to_string());
    EXPECT_EQ(pol6.to_string(), get6.to_string());

}
TEST(HashNextTable, insert_and_get_ord) {
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
    Node n4;
    n4.name = "pol4";
    Polynome pol4 = Polynome{ "x+y+z" };
    n4.data = pol4;
    Node n5;
    n5.name = "pol5";
    Polynome pol5 = Polynome{ "x+y+z" };
    n5.data = pol5;
    Node n6;
    Polynome pol6 = Polynome{ "x*y*z" };
    n6.name = "pol6";
    n6.data = pol6;
    // table
    HashNextTable table;
    // insert
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    table.Insert(n4);
    table.Insert(n5);
    table.Insert(n6);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");
    Polynome get4 = table.Take_elem("pol4");
    Polynome get5 = table.Take_elem("pol5");
    Polynome get6 = table.Take_elem("pol6");

    EXPECT_EQ(pol1.to_string(), get1.to_string());
    EXPECT_EQ(pol2.to_string(), get2.to_string());
    EXPECT_EQ(pol3.to_string(), get3.to_string());
    EXPECT_EQ(pol4.to_string(), get4.to_string());
    EXPECT_EQ(pol5.to_string(), get5.to_string());
    EXPECT_EQ(pol6.to_string(), get6.to_string());

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
    OrderedTB table;
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

TEST(Tree, insert_and_get_astable) {
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
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);
    // get back
    Polynome get1 = table.Take_elem("pol1");
    Polynome get2 = table.Take_elem("pol2");
    Polynome get3 = table.Take_elem("pol3");

    EXPECT_EQ(pol1.to_string(), get1.to_string());
    EXPECT_EQ(pol2.to_string(), get2.to_string());
    EXPECT_EQ(pol3.to_string(), get3.to_string());
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
TEST(Tree, delete_elem_astable) {
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
    table.Insert(n1);
    table.Insert(n2);
    table.Insert(n3);

    ASSERT_NO_THROW(table.Del(n2.name));
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

