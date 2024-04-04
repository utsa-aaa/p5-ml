#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_default_ctor) {
    BinarySearchTree<int> BST;

    ASSERT_TRUE(BST.empty());
    ASSERT_EQUAL(BST.height(), 0u);
    ASSERT_EQUAL(BST.size(), 0u);

    BinarySearchTree<int> &BST2 = BST;
    //self assignment
    BST = BST2;
    ASSERT_TRUE(BST.empty());
    ASSERT_EQUAL(BST.height(), 0u);
    ASSERT_EQUAL(BST.size(), 0u);

    auto it_min = BST.min_element();
    auto it_max = BST.max_element();
    auto it_end = BST.end();

    ASSERT_EQUAL(it_min, it_end);
    ASSERT_EQUAL(it_max, it_end);

}

TEST(test_non_default_ctor) {
    BinarySearchTree<int> BST;
    BST.insert(4);
    BST.insert(2);
    BST.insert(6);
    BST.insert(1);
    BST.insert(3);
    BST.insert(5);
    BST.insert(7);
    ASSERT_FALSE(BST.empty());
    ASSERT_EQUAL(BST.height(), 3u);
    ASSERT_EQUAL(BST.size(), 7u);

    BinarySearchTree<int> BST2(BST);
    ASSERT_EQUAL(BST.height(), 3u);
    ASSERT_EQUAL(BST.size(), 7u);

    auto it_end = BST.end();
    ASSERT_EQUAL(BST.find(20), it_end);

    auto it_beg = BST.begin();
    ASSERT_EQUAL(BST.find(4), it_beg);

    auto it_max = BST.max_element();
    ASSERT_EQUAL(*it_max, 7);
}

TEST(test_height) {
    BinarySearchTree<int> BST;
    BST.insert(1);
    BST.insert(2);
    BST.insert(4);
    BST.insert(6);
    BST.insert(8);
    ASSERT_EQUAL(BST.height(), 5u);
    ASSERT_EQUAL(BST.size(), 5u);

    auto it_min = BST.min_element();
    auto it_begin = BST.begin();

    ASSERT_EQUAL(it_min, it_begin);

    auto it_max = BST.max_element();
    ASSERT_EQUAL(*it_max, 8);

    it_begin++;
    ASSERT_EQUAL(*it_begin, 2);


}

TEST(test_branch_and_copy) {
    BinarySearchTree<int> BST;
    BST.insert(10);
    BST.insert(9);
    BST.insert(8);
    BST.insert(5);
    BST.insert(3);
    ASSERT_EQUAL(BST.height(), 5u);
    ASSERT_EQUAL(BST.size(), 5u);

    BinarySearchTree<int> BST2;
    BST2 = BST;
    auto it_max = BST2.max_element();
    auto it_begin = BST2.begin();

    ASSERT_EQUAL(it_max, it_begin);
    
    auto it_min = BST2.min_element();
    ASSERT_EQUAL(*it_min, 3);

    ASSERT_EQUAL(BST2.height(), 5u);
    ASSERT_EQUAL(BST2.size(), 5u);

}


TEST_MAIN()
