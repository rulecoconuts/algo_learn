#include <catch2/catch_test_macros.hpp>
#include "../src/b_tree.h"
#include "../src/iterative_b_tree_node_searcher.h"

TEST_CASE("Iterative BTreeNodeSearcher find()", "[IterativeBTreeNodeSearcher]")
{
    std::shared_ptr<BTreeNodeSearcher<int>> nodeSearcher = std::make_shared<IterativeBTreeNodeSearcher<int>>();
    std::shared_ptr<BTreeNodeValidator<int>> nodeValidator = std::make_shared<DefaultBTreeNodeValidator<int>>();
    int maxKeys = 5;
    BTree tree = BTree(maxKeys, nodeValidator, nodeSearcher);

    SECTION("able to find key when it is the only key inserted")
    {
        int key = 4;
        tree.insert(key);
        int *foundKey = tree.find(key);

        REQUIRE(foundKey != nullptr);
        REQUIRE(*(foundKey) == key);
    }

    SECTION("able to find key after multiple inserted")
    {
        tree.insert(40);
        tree.insert(20);
        tree.insert(2);
        tree.insert(1);
        int key = 55;
        tree.insert(key);
        int *foundKey = tree.find(key);

        REQUIRE(foundKey != nullptr);
        REQUIRE(*(foundKey) == key);
    }
}