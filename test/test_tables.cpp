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
    ASSERT_NO_THROW(OrderedTB table{});
}
TEST(Tree, can_create_table) {
    ASSERT_NO_THROW(Tree table{});
}