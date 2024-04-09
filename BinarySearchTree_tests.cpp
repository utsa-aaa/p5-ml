
#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;

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
    ASSERT_NOT_EQUAL(BST.begin(), BST2.begin());


    auto it_end = BST.end();
    ASSERT_EQUAL(BST.find(20), it_end);

    auto it_beg = BST.begin();
    ASSERT_EQUAL(BST.find(1), it_beg);

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

    BinarySearchTree<int> BST2;
    BST2.insert(1);
    ASSERT_EQUAL(BST2.height(), 1u);
    ASSERT_EQUAL(BST2.size(), 1u);

    BinarySearchTree<int> BST3;
    ASSERT_EQUAL(BST3.height(), 0u);
    ASSERT_EQUAL(BST3.size(), 0u);

    BinarySearchTree<int> BST4(BST3);
    ASSERT_EQUAL(BST4.height(), 0u);
    ASSERT_EQUAL(BST4.size(), 0u);



}

TEST(test_branch_and_copy) {
    BinarySearchTree<int> BST;
    BST.insert(10);
    BST.insert(9);
    BST.insert(8);
    ASSERT_TRUE(BST.check_sorting_invariant());
    BST.insert(5);
    BST.insert(3);
    ASSERT_TRUE(BST.check_sorting_invariant());
    ASSERT_EQUAL(BST.height(), 5u);
    ASSERT_EQUAL(BST.size(), 5u);

    BinarySearchTree<int> BST2;
    BST2 = BST;
    auto it_min = BST2.min_element();
    auto it_begin = BST2.begin();


    ASSERT_EQUAL(it_min, it_begin);
    
    ASSERT_EQUAL(*it_min, 3);

    ASSERT_EQUAL(BST2.height(), 5u);
    ASSERT_EQUAL(BST2.size(), 5u);

}
TEST(test_copy2) {
    BinarySearchTree<int> BST;
    BST.insert(1);
    auto it_begin = BST.begin();

    BinarySearchTree<int> BST2;
    BST2.insert(1);
    auto it_begin2 = BST2.begin();
    ASSERT_NOT_EQUAL(it_begin, it_begin2);
    BinarySearchTree<int> &BST3 = BST;
    BST = BST3;
    ASSERT_EQUAL(it_begin, BST.begin());

}

TEST(test_increment) {
    BinarySearchTree<int> BST;
    BST.insert(4);
    BST.insert(2);
    BST.insert(6);
    ASSERT_TRUE(BST.check_sorting_invariant());
    BST.insert(1);
    BST.insert(3);
    BST.insert(5);
    ASSERT_TRUE(BST.check_sorting_invariant());
    BST.insert(7);

    auto it_begin = BST.begin();
    ASSERT_EQUAL(*it_begin, 1);
    ++it_begin;
    ASSERT_EQUAL(*it_begin, 2);
    ++it_begin;
    ASSERT_EQUAL(*it_begin, 3);



    BinarySearchTree<int> BST2;
    ASSERT_TRUE(BST2.check_sorting_invariant());
    BST2.insert(10);
    BST2.insert(9);
    BST2.insert(8);
    ASSERT_TRUE(BST2.check_sorting_invariant());
    BST2.insert(5);
    BST2.insert(3);

    auto it_begin2 = BST2.begin();
    ASSERT_EQUAL(*it_begin2, 3);
    ++it_begin2;
    ASSERT_EQUAL(*it_begin2, 5);
    ++it_begin2;
    ASSERT_EQUAL(*it_begin2, 8);

    ASSERT_TRUE(BST2.check_sorting_invariant());
    ASSERT_TRUE(BST.check_sorting_invariant());



}
TEST(test_increment2) {
    BinarySearchTree<int> BST;
    BST.insert(4);
    auto it_begin = BST.begin();
    ++it_begin;
    ASSERT_EQUAL(it_begin, BST.end());

}

TEST(test_in_order) {
 BinarySearchTree<int> BST;
 BST.insert(10);
 BST.insert(9);
 BST.insert(8);
 BST.insert(5);
 BST.insert(3);


 ostringstream oss_inorder;
 BST.traverse_inorder(oss_inorder);
 ASSERT_TRUE(oss_inorder.str() == "3 5 8 9 10 ");

 BinarySearchTree<int> BST2;
 BST2.insert(1);
 BST2.insert(2);
 BST2.insert(4);
 BST2.insert(6);
 BST2.insert(8);


 ostringstream oss_inorder2;
 BST2.traverse_inorder(oss_inorder2);
 ASSERT_TRUE(oss_inorder2.str() == "1 2 4 6 8 ");

 BinarySearchTree<int> BST3;
 BST3.insert(4);
 BST3.insert(2);
 BST3.insert(6);
 BST3.insert(1);
 BST3.insert(3);
 BST3.insert(5);
 BST3.insert(7);

 ostringstream oss_inorder3;
 BST3.traverse_inorder(oss_inorder3);
 ASSERT_TRUE(oss_inorder3.str() == "1 2 3 4 5 6 7 ");

 BinarySearchTree<int> BST4;
 ostringstream oss_inorder4;
 BST4.traverse_inorder(oss_inorder4);
 ASSERT_TRUE(oss_inorder4.str() == "");

}

TEST(test_pre_order){
    BinarySearchTree<int> BST;
    BST.insert(45);
    BST.insert(25);
    BST.insert(15);
    BST.insert(35);
    BST.insert(75);
    ostringstream oss_preorder;
    BST.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "45 25 15 35 75 ");


    // BinarySearchTree<int> BST2;
    // BST2.insert(1);
    // BST2.insert(2);
    // BST2.insert(3);
    // BST2.insert(4);
    // BST2.insert(5);
    // BST2.insert(6);
    // BST2.insert(7);
    // ostringstream oss_preorder2;
    // BST.traverse_preorder(oss_preorder2);
    // // ASSERT_TRUE(oss_preorder2.str() == "4 2 1 3 6 5 7 ");



    BinarySearchTree<int> BST3;
    ostringstream oss_preorder3;
    BST3.traverse_preorder(oss_preorder3);
    ASSERT_TRUE(oss_preorder3.str() == "");




}

TEST(test_find){
    BinarySearchTree<int> BST;
    BST.insert(4);
    BST.insert(2);
    BST.insert(5);
    BST.insert(7);
    ASSERT_EQUAL(BST.find(2), BST.min_element());

    BinarySearchTree<int> BST2;
    BST2.insert(1);
    BST2.insert(2);
    BST2.insert(4);
    BST2.insert(6);
    BST2.insert(8);
    auto it_end = BST2.end();
    ASSERT_EQUAL(BST2.find(3), it_end);

    BinarySearchTree<int> BST3;
    auto it_end_2 = BST3.end();
    ASSERT_EQUAL(BST3.find(5), it_end_2);

    BinarySearchTree<int> BST4;
    BST4.insert(1);
    ASSERT_EQUAL(BST4.find(1), BST4.begin());

}

TEST(test_min){
    BinarySearchTree<int> BST;
    BST.insert(2);
    BST.insert(4);
    BST.insert(5);
    BST.insert(7);
    ASSERT_EQUAL(*BST.min_element(),2);
    
    BinarySearchTree<int> BST2;
    BST2.insert(6);
    BST2.insert(2);
    BST2.insert(3);
    BST2.insert(1);
    ASSERT_EQUAL(*BST2.min_element(),1);

    BinarySearchTree<int> BST3;
    auto it_end = BST3.end();
    ASSERT_EQUAL(BST3.min_element(), it_end);

    BinarySearchTree<int> BST4;
    BST4.insert(4);
    ASSERT_EQUAL(*BST4.min_element(),4);
    ASSERT_TRUE(BST4.check_sorting_invariant());
    ASSERT_EQUAL(BST4.min_element(),BST4.begin());

    BinarySearchTree<int> BST5;
    BST5.insert(-10);
    ASSERT_EQUAL(*BST5.min_element(),-10);
    BST5.insert(-20);
    ASSERT_EQUAL(*BST5.min_element(),-20);
    ASSERT_EQUAL(*BST5.max_element(),-10);


}


TEST(test_max){
    BinarySearchTree<int> BST;
    BST.insert(4);
    BST.insert(2);
    BST.insert(5);
    BST.insert(7);
    ASSERT_EQUAL(*BST.max_element(),7);
    
    BinarySearchTree<int> BST2;
    BST2.insert(7);
    BST2.insert(1);
    BST2.insert(9);
    BST2.insert(6);
    BST2.insert(8);
    ASSERT_EQUAL(*BST2.max_element(),9);

    BinarySearchTree<int> BST3;
    auto it_end = BST3.end();
    ASSERT_EQUAL(BST3.max_element(), it_end);

    BinarySearchTree<int> BST4;
    BST4.insert(4);
    ASSERT_EQUAL(*BST4.max_element(),4);
    ASSERT_EQUAL(BST4.max_element(),BST4.begin());


    BinarySearchTree<int> BST5;
    BST5.insert(0);
    BST5.insert(-10);
    ASSERT_EQUAL(*BST5.max_element(),0);
    ASSERT_EQUAL(*BST5.min_element(),-10);

    BinarySearchTree<int> BST6;
    BST6.insert(-20);
    BST6.insert(-10);
    ASSERT_EQUAL(*BST6.max_element(),-10);


}

TEST(test_min_greater_than){
    BinarySearchTree<int> BST;
    auto it_end = BST.end();
    ASSERT_EQUAL(BST.min_greater_than(65), it_end);

    BinarySearchTree<int> BST2;
    BST2.insert(7);
    BST2.insert(1);
    BST2.insert(8);
    BST2.insert(6);
    BST2.insert(9);
    ASSERT_EQUAL(*BST2.min_greater_than(1), 6);
    ASSERT_EQUAL(*BST2.min_greater_than(6), 7);

    BinarySearchTree<int> BST3;
    BST3.insert(9);
    BST3.insert(6);
    BST3.insert(4);
    BST3.insert(8);
    auto it_end3 = BST3.end();
    ASSERT_EQUAL(BST3.min_greater_than(9), it_end3);
    ASSERT_EQUAL(BST3.min_greater_than(10), it_end3);
    ASSERT_EQUAL(*BST3.min_greater_than(8), 9);
    

}

TEST(test_min_greater_than2){
    BinarySearchTree<int> BST;
    auto it_end = BST.end();
    ASSERT_EQUAL(BST.min_greater_than(65), it_end);

    BinarySearchTree<int> BST2;
    BST2.insert(7);
    BST2.insert(1);
    BST2.insert(8);
    BST2.insert(6);
    BST2.insert(9);
    ASSERT_EQUAL(*BST2.min_greater_than(1), 6);

    BinarySearchTree<int> BST3;
    BST3.insert(9);
    BST3.insert(6);
    BST3.insert(4);
    BST3.insert(8);
    auto it_end3 = BST3.end();
    ASSERT_EQUAL(BST3.min_greater_than(9), it_end3);
}


TEST(test_strings) {
    BinarySearchTree<string> BST;
    BST.insert("Hello");
    BST.insert("World");
    BST.insert("!!");
    ASSERT_EQUAL(*BST.min_greater_than("Hello"), "World");
    ASSERT_EQUAL(*BST.max_element(), "World");
    ASSERT_EQUAL(*BST.begin(), "!!");
    ASSERT_EQUAL(BST.find("!!"), BST.begin());
    ASSERT_EQUAL(BST.find("Hel"), BST.end());
    ASSERT_EQUAL(*(++(BST.find("Hello"))), "World");
    ASSERT_EQUAL(BST.height(), 2u);
    ASSERT_EQUAL(BST.size(), 3u);

    BinarySearchTree<string> BST2(BST);
    ASSERT_EQUAL(*BST2.min_greater_than("Hello"), "World");
    ASSERT_EQUAL(*BST2.max_element(), "World");
    ASSERT_EQUAL(*BST2.begin(), "!!");
    ASSERT_EQUAL(BST2.find("!!"), BST2.begin());
    ASSERT_EQUAL(BST2.find("Hel"), BST2.end());
    ASSERT_EQUAL(*(++(BST2.find("Hello"))), "World");
    ASSERT_EQUAL(BST2.height(), 2u);
    ASSERT_EQUAL(BST2.size(), 3u);


 

}

TEST(test_iterators_empty) {
    BinarySearchTree<int> BST;
    ASSERT_EQUAL(BST.begin(), BST.end());
    ASSERT_TRUE(BST.check_sorting_invariant());
}
TEST(test_assignment2) {
    BinarySearchTree<int> BST;
    BST.insert(10);
    BST.insert(5);
    BST.insert(15);
    
    BinarySearchTree<int> BST2 = BST;
    BST.insert(3);
    BST2.insert(20);
    
    ASSERT_EQUAL(BST.size(), 4u);
    ASSERT_EQUAL(BST2.size(), 4u);
    ASSERT_TRUE(BST.find(3) != BST.end());
    ASSERT_TRUE(BST2.find(20) != BST2.end());
    ASSERT_TRUE(BST.find(20) == BST.end());
    ASSERT_TRUE(BST2.find(3) == BST2.end());
}

TEST(test_edge) {
    BinarySearchTree<int> BST;
    BST.insert(999999);
    BST.insert(-999999);
    BST.insert(0);

    ASSERT_TRUE(BST.find(999999) != BST.end());
    ASSERT_TRUE(BST.find(-999999) != BST.end());
    ASSERT_TRUE(BST.find(0) != BST.end());
    ASSERT_EQUAL(BST.size(), 3u);
    ASSERT_EQUAL(*BST.min_element(), -999999);
    ASSERT_EQUAL(*BST.max_element(), 999999);
    ASSERT_EQUAL(BST.find(-999999),  BST.begin());

}
TEST_MAIN()
